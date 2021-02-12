/**
 * \file MachineDemoView.h
 *
 * \author Charles Owen
 *
 * A view window that displays a single machine object
 */

#pragma once

#include <memory>
#include "Machine.h"

/**
 * A view window that displays a single machine object
 */
class CMachineDemoView : public CWnd
{
	DECLARE_DYNAMIC(CMachineDemoView)

public:
	CMachineDemoView();
	virtual ~CMachineDemoView();

    void SetFrame(int frame);
    void SetMachineNumber(int machine);
    void SetScale(double scale);

    /**
     * Get the machine object
     * 
     * You are not allowed to do this in your adapter class!
     * \return CMachine object
     */
    std::shared_ptr<CMachine> GetMachine() { return mMachine; }

protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);

    BOOL Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle);

private:
    double mScale = 1.0;                ///< Amount to scale the image

    BOOL RegisterWindowClass();

    std::shared_ptr<CMachine> mMachine;       ///< Machine we are displaying
public:
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};


