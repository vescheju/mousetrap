/**
 * \file Pin.cpp
 *
 * \author Justin Vesche
 */

#include "pch.h"
#include "Pin.h"

/// The limit of how far a pin can be moved 
/// in the X direction in pixels. At this 
/// limit the winch is stopped.
const double PinXLimit = 65;

/**
* Constructor
*/
CPin::CPin()
{

}

/**
 * Destructor
 */
CPin::~CPin()
{
}

/**
* Draw our winch and the string
* \param graphics The graphics context to draw on
* \param x the x location to draw at
* \param y the y location to draw at
*/
void CPin::Draw(Gdiplus::Graphics* graphics, int x, int y)
{
	CComponent::Draw(graphics, x, y);
	mChange = 0;
}

/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CPin::Update(double elapsed)
{
	// Move the pin if it has not reached the end
	auto pos = GetPosition();
	if (mStartPositionX.X - pos.X  < PinXLimit)
	{
		CComponent::SetPosition(Gdiplus::Point(mStartPositionX.X - mChange, pos.Y));
		mEnd = false;
	}
	else
	{
		mEnd = true; 
		mChange = 0;
	}

}
/**
* A reset function
* Restarts the pins location.
*/
void CPin::Reset()
{
	CComponent::SetPosition(mStartPositionX);
	mEnd = false;
	mChange = 0;
}

/**
* A function that overrides the SetPosition function
* 
* \param pos the position of the new pin location
*/
void CPin::SetPosition(Gdiplus::Point pos)
{
	mEnd = false;
	mStartPositionX = pos;
	CComponent::SetPosition(pos);
	mChange = 0;
}
