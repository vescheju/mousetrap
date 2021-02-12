/**
 * \file Adapter.cpp
 *
 * \author Justin Vesche
 */

#include "pch.h"
#include "Adapter.h"

/**
* Destructor
*/
CAdapter::~CAdapter()
{
}


/**
 * Constructor
 * \param name The name of the adapter
 */
CAdapter::CAdapter(const std::wstring& name) : CDrawable(name)
{
    CMachineFactory factory;
    mMachine = factory.CreateMachine();
   
}

/** Draw the drawable
* \param graphics Graphics object to draw on */
void CAdapter::Draw(Gdiplus::Graphics* graphics)
{
    float scale = 0.8f;
    auto save = graphics->Save();
    graphics->TranslateTransform((float)mPlacedPosition.X,
        (float)mPlacedPosition.Y);
    graphics->ScaleTransform(scale, scale);
    mMachine->DrawMachine(graphics);
    graphics->Restore(save);
}

/**
* Test to see if we have been clicked our machine
* \param position Position to test
* \return true if clicked on
*/
bool CAdapter::HitTest(Gdiplus::Point position)
{
    return false;
}

/**
* Test to see if we have been clicked our machine
* \param num the number of the machine number, so it can change.
*/
void CAdapter::SetMachineNumber(int num)
{
    mMachine->SetMachineNumber(num);
}

/**
* Pulls up the box so the machine can be changed.
*/
void CAdapter::MachineImp()
{
    CMachineDlg dlg(mMachine);
    if (dlg.DoModal() == IDOK)
    {
        // A machine has been selected
    }
}

/**
* Set the mouse trap frame.
* \param num the frame the mouse trap will be set as
*/
void CAdapter::SetFrame(int num)
{
    mMachine->SetMachineFrame(num);
}




