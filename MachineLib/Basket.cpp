/**
 * \file Basket.cpp
 *
 * \author Justin Vesche
 */

#include "pch.h"
#include "Basket.h"


/// The rate the trap falls when it is sprung
/// in pixels per second. 
const double TrapFallRate = 200;

/// This is how far up the image trap-trap.png
/// is moved in pixels when it is initially set. 
const double TrapUpY = 100;

/**
 * Destructor
 */
CBasket::~CBasket()
{
}

/**
 * Constructor
 */
CBasket::CBasket()
{
	
}
/**
* Draw our basket
* \param graphics The graphics context to draw on
* \param x the x location to draw at
* \param y the y location to draw at
*/
void CBasket::Draw(Gdiplus::Graphics* graphics, int x, int y)
{
	CComponent::Draw(graphics, x, y);
}

/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CBasket::Update(double elapsed)
{
	auto pos = GetPosition();
	auto length = 200 * elapsed;
	if (pos.Y - mStartPosY  < TrapUpY)
	{
		CComponent::SetPosition(Gdiplus::Point(pos.X, pos.Y + length));
	}
	
	

}
/** A function that resets the basket
*/
void CBasket::Reset()
{
	SetPosition(Gdiplus::Point(GetPosition().X, mStartPosY));
}

/** Set the componets position
* \param pos The new componets position*/
void CBasket::SetPosition(Gdiplus::Point pos)
{
	mStartPosY = pos.Y;
	CComponent::SetPosition(pos);
}
