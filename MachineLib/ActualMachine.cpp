/**
 * \file ActualMachine.cpp
 *
 * \author Justin Vesche
 */


#include "pch.h"
#include "ActualMachine.h"

 /** Handle updates for animation
 * \param elapsed The time since the last update
 */
void CActualMachine::Update(double elapsed)
{
	for (auto item : mComponents)
	{
		item->Update(elapsed);
	}
}

/**
 * Draw our draw function that draws each component
 * \param graphics The graphics context to draw on
 */
void CActualMachine::Draw(Gdiplus::Graphics* graphics)
{
	for (auto item : mComponents)
	{
		item->Draw(graphics, mX, mY);
	}
}

/**
* Add each the component to our machine
* \param component the component to be added to our machine.
*/
void CActualMachine::AddComponent(std::shared_ptr<CComponent> component)
{
	mComponents.push_back(component);
}

/** A function that resets everything
*/
void CActualMachine::Reset()
{
	for (auto item : mComponents)
	{
		item->Reset();
	}
}

/**
 * Constructor
 */
CActualMachine::CActualMachine()
{

}


/**
 * Destructor
 */
CActualMachine::~CActualMachine()
{
}
