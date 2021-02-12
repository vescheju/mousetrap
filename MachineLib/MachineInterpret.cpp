/**
 * \file MachineInterpret.cpp
 *
 * \author Justin Vesche
 */

#include "pch.h"
#include "MachineInterpret.h"
#include "MachineFactory1.h"
#include "MachineFactory2.h"

/// A constant of the framerate of the machine
const int FrameRate = 30;

/**
 * Constructor
 *  Default machine to 1;
 */
CMachineInterpret::CMachineInterpret() : CMachine()
{
    
    SetMachineNumber(1);
}

/**
* Set the location of our machine
* \param x and int of our x location machine will be set at
* \param y and int of our y location machine will be set at
*/
void CMachineInterpret::SetLocation(int x, int y)
{
    mMachine->SetLocation(Gdiplus::Point(x, y));
}

/**
* Draw our machine
* \param graphics the graphics that will be used to draw
*/
void CMachineInterpret::DrawMachine(Gdiplus::Graphics* graphics)
{
    mMachine->Draw(graphics);
}

/**
* This class handles the updating and reseting of the frames
* \param frame the frame we should be at, calling update
*/
void CMachineInterpret::SetMachineFrame(int frame)
{
    if (frame < mMachine->GetFrame())
    {
        mMachine->SetFrame(0);
        mMachine->Reset();
    }

    while (mMachine->GetFrame() < frame) {
        mMachine->SetFrame(mMachine->GetFrame() + 1);
        mMachine->Update(1.0 / FrameRate);
    }
	
}


/**
* Set the machine number
* \param machine An integer number. Each integer makes a different machine
*/
void CMachineInterpret::SetMachineNumber(int machine)
{
	
    if (machine == 1)
    {
        CMachineFactory1 factory;
        mMachine = factory.CreateMachine();   
    }
    else
    {
        CMachineFactory2 factory;
        mMachine = factory.CreateMachine();
    }
    mMachine->SetMachine(machine);
}

/**
* Get the current machine number
* \return Machine number
*/
int CMachineInterpret::GetMachineNumber()
{
	return mMachine->GetMachine();
}



