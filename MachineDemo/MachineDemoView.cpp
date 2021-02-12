/**
 * \file MachineDemoView.cpp
 *
 * \author Charles Owen
 */

#include "pch.h"
#include "MachineDemo.h"
#include "MachineDemoView.h"
#include "DoubleBufferDC.h"
#include "MachineFactory.h"

using namespace Gdiplus;

// Window class name for this view
#define VIEWER_CLASSNAME    _T("CMachineDemoView")  // Window class name

IMPLEMENT_DYNAMIC(CMachineDemoView, CWnd)

/**
 * Constructor
 */
CMachineDemoView::CMachineDemoView()
{
    RegisterWindowClass();

    //
    // Use a factory to create the machine object
    //
    CMachineFactory factory;
    mMachine = factory.CreateMachine();
}

/**
 * Destructor
 */
CMachineDemoView::~CMachineDemoView()
{
}

/**
 * Register this view as  a window
 * \return TRUE if successful
 */
BOOL CMachineDemoView::RegisterWindowClass()
{
    WNDCLASS wndcls;
    HINSTANCE hInst = AfxGetInstanceHandle();

    if (!(::GetClassInfo(hInst, VIEWER_CLASSNAME, &wndcls)))
    {
        // otherwise we need to register a new class
        wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        wndcls.lpfnWndProc = ::DefWindowProc;
        wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
        wndcls.hInstance = hInst;
        wndcls.hIcon = NULL;
        wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        wndcls.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
        wndcls.lpszMenuName = NULL;
        wndcls.lpszClassName = VIEWER_CLASSNAME;

        if (!AfxRegisterClass(&wndcls))
        {
            AfxThrowResourceException();
            return FALSE;
        }
    }

    return TRUE;
}


/**
 * Create the view
 * \param pParentWnd Optional parent window
 * \param rect View rectanlge
 * \param nID ID for the view
 * \param dwStyle Window style
 * \returns true if successful
 */
BOOL CMachineDemoView::Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle /*=WS_VISIBLE*/)
{
    dwStyle |= WS_HSCROLL | WS_VSCROLL;

    int rootX = rect.right / 2;
    int rootY = rect.bottom - 100;
    mMachine->SetLocation(rootX, rootY);

	return CWnd::CreateEx(WS_EX_CLIENTEDGE, VIEWER_CLASSNAME, _T(""), dwStyle, rect, pParentWnd, nID);
    //return CWnd::Create(VIEWER_CLASSNAME, _T(""), dwStyle, rect, pParentWnd, nID);
}

/** \cond */
BEGIN_MESSAGE_MAP(CMachineDemoView, CWnd)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_VSCROLL()
    ON_WM_HSCROLL()
END_MESSAGE_MAP()
/** \endcond */


/**
 * Paint the view
 */
void CMachineDemoView::OnPaint()
{
    CPaintDC paintDC(this);     // device context for painting
    CDoubleBufferDC dc(&paintDC); // device context for painting

    Graphics graphics(dc.m_hDC);    // Create GDI+ graphics context

    CRect rect;
    GetClientRect(&rect);
    int rootX = rect.right / 2;
    int rootY = rect.bottom - 100;

    SCROLLINFO hScrollInfo;
    GetScrollInfo(SB_HORZ, &hScrollInfo);
    hScrollInfo.nMin = 0;
    hScrollInfo.nMax = (int)(rect.Width() * mScale);
    hScrollInfo.nPage = rect.Width();
    SetScrollInfo(SB_HORZ, &hScrollInfo);


    SCROLLINFO vScrollInfo;
    GetScrollInfo(SB_VERT, &vScrollInfo);
    vScrollInfo.nMin = 0;
    vScrollInfo.nMax = (int)(rect.Height() * mScale);
    vScrollInfo.nPage = rect.Height();
    SetScrollInfo(SB_VERT, &vScrollInfo);

    auto save = graphics.Save();
    graphics.TranslateTransform((REAL)-hScrollInfo.nPos, (REAL)-vScrollInfo.nPos);
    graphics.ScaleTransform((REAL)mScale, (REAL)mScale);
    
    mMachine->SetLocation(rootX, rootY);
    mMachine->DrawMachine(&graphics);

    graphics.Restore(save);
}


/**
 * Handle an erase background message. Since we use CDoubleBufferDC, we ignore it
 * \param pDC Device context
 * \returns FALSE
 */
BOOL CMachineDemoView::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}


/**
 * Set the current view frame
 * \param frame Frame number
 */
void CMachineDemoView::SetFrame(int frame) 
{
    mMachine->SetMachineFrame(frame);
    Invalidate();
}




/**
 * Set the machine number
 * \param machine Machine number
 */
void CMachineDemoView::SetMachineNumber(int machine)
{
    mMachine->SetMachineNumber(machine);
}

/**
 * Set the machine drawing scale
 * \param scale Drawing scale, 1.0 is normal size.
*/
void CMachineDemoView::SetScale(double scale)
{
    CRect rect;
    GetClientRect(&rect);

    SCROLLINFO hScrollInfo;
    GetScrollInfo(SB_HORZ, &hScrollInfo);
    hScrollInfo.nMin = 0;
    hScrollInfo.nMax = (int)(rect.Width() * scale);
    hScrollInfo.nPage = rect.Width();
    auto newCenter = (int)(hScrollInfo.nPos + rect.Width() / 2) * scale / mScale;
    hScrollInfo.nPos = (int)(newCenter - rect.Width() / 2);
    SetScrollInfo(SB_HORZ, &hScrollInfo);


    SCROLLINFO vScrollInfo;
    GetScrollInfo(SB_VERT, &vScrollInfo);
    vScrollInfo.nMin = 0;
    vScrollInfo.nMax = (int)(rect.Height() * scale);
    vScrollInfo.nPage = rect.Height();
    newCenter = (int)(vScrollInfo.nPos + rect.Width() / 2) * scale / mScale;
    vScrollInfo.nPos = (int)(newCenter - rect.Width() / 2);
    SetScrollInfo(SB_VERT, &vScrollInfo);


    mScale = scale;


    Invalidate();
}


/**
 * Handle a vertical scrollbar message
 * \param nSBCode Message code
 * \param nPos New scroll bar position
 * \param pScrollBar Scrollbar we are adjusting
 */
void CMachineDemoView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // Get all the vertical scroll bar information.
    SCROLLINFO si;
    si.cbSize = sizeof(si);
    si.fMask = SIF_ALL;

    // Save the position for comparison later on.
    GetScrollInfo(SB_VERT, &si);
    int xPos = si.nPos;
    switch (nSBCode)
    {
        // User clicked the left arrow.
    case SB_LINELEFT:
        si.nPos -= 1;
        break;

        // User clicked the right arrow.
    case SB_LINERIGHT:
        si.nPos += 1;
        break;

        // User clicked the scroll bar shaft left of the scroll box.
    case SB_PAGELEFT:
        si.nPos -= si.nPage;
        break;

        // User clicked the scroll bar shaft right of the scroll box.
    case SB_PAGERIGHT:
        si.nPos += si.nPage;
        break;

        // User dragged the scroll box.
    case SB_THUMBTRACK:
        si.nPos = si.nTrackPos;
        break;

    default:
        break;
    }

    // Set the position and then retrieve it.  Due to adjustments
    // by Windows it may not be the same as the value set.
    si.fMask = SIF_POS;
    SetScrollInfo(SB_VERT, &si, TRUE);
    GetScrollInfo(SB_VERT, &si);

    // If the position has changed, scroll the window.
    if (si.nPos != xPos)
    {
        Invalidate();
    }

    CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}


/**
 * Handle a horizontal scrollbar message.
 * \param nSBCode Message code
 * \param nPos New scroll bar position
 * \param pScrollBar Scrollbar we are adjusting
 */
void CMachineDemoView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // Get all the vertial scroll bar information.
    SCROLLINFO si;
    si.cbSize = sizeof(si);
    si.fMask = SIF_ALL;

    // Save the position for comparison later on.
    GetScrollInfo(SB_HORZ, &si);
    int xPos = si.nPos;
    switch (nSBCode)
    {
        // User clicked the left arrow.
    case SB_LINELEFT:
        si.nPos -= 1;
        break;

        // User clicked the right arrow.
    case SB_LINERIGHT:
        si.nPos += 1;
        break;

        // User clicked the scroll bar shaft left of the scroll box.
    case SB_PAGELEFT:
        si.nPos -= si.nPage;
        break;

        // User clicked the scroll bar shaft right of the scroll box.
    case SB_PAGERIGHT:
        si.nPos += si.nPage;
        break;

        // User dragged the scroll box.
    case SB_THUMBTRACK:
        si.nPos = si.nTrackPos;
        break;

    default:
        break;
    }

    // Set the position and then retrieve it.  Due to adjustments
    // by Windows it may not be the same as the value set.
    si.fMask = SIF_POS;
    SetScrollInfo(SB_HORZ, &si, TRUE);
    GetScrollInfo(SB_HORZ, &si);

    // If the position has changed, scroll the window.
    if (si.nPos != xPos)
    {
        Invalidate();
    }
    
    CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}
