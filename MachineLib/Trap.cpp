/**
 * \file Trap.cpp
 *
 * \author Justin Vesche
 */

#include "pch.h"
#include "Trap.h"


/// Size I draw the trap in pixels(square)
const int Size = 300;

/// This is how far up the image trap-trap.png
/// is moved in pixels when it is initially set. 
const double TrapUpY = -150;

/// This is how far up the image trap-trap.png
/// is moved in pixels when it is initially set. 
const double BasketUpY = -100;

/// The rate the trap falls when it is sprung
/// in pixels per second. 
const double TrapFallRate = 200;


/// How far out a pin must be removed to release
/// the trap in pixels. 
const double PinRemoved = 19;

/**
 * Destructor
 */
CTrap::~CTrap()
{
}

/**
* Constructor
*/
CTrap::CTrap()
{
	// Set the pin, basket, and the base to images.
	mFront = std::make_shared<CPolygon>();
	mPin = std::make_shared<CPin>();
	mBasket = std::make_shared<CBasket>();
	CenteredSquare(Size);
	
	SetImage(L"images/trap-stand.png");

	mFront->CenteredSquare(Size);

	mFront->SetImage(L"images/trap-stand-front.png");

	mPin->CenteredSquare(Size);
	mPin->SetImage(L"images/trap-pin.png");

	mBasket->CenteredSquare(Size);
	mBasket->SetImage(L"images/trap-trap.png");


}

/**
* Draw our winch and the string
* \param graphics The graphics context to draw on
* \param x the x location to draw at
* \param y the y location to draw at
*/
void CTrap::Draw(Gdiplus::Graphics* graphics, int x, int y)
{
	// Call draw for each component, because basket owns them.
	CComponent::Draw(graphics, x, y + TrapUpY);
	Gdiplus::Point pos = GetPosition();
	mPin->Draw(graphics, x, y + TrapUpY);
	mBasket->Draw(graphics, x, y + TrapUpY + BasketUpY);
	mFront->DrawPolygon(graphics, x + pos.X, y + TrapUpY + pos.Y);
	
	
}

/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CTrap::Update(double elapsed)
{
	// Calls pin update
	mPin->Update(elapsed);
	auto x = mPin->GetStart().X - mPin->GetPosition().X ;
	// only calls if pin is moved enough.
	if (x > PinRemoved)
	{
		mBasket->Update(elapsed);
	}
	
}

/**
* A reset function
* Restarts the whole basket.
*/
void CTrap::Reset()
{
	mBasket->Reset();
	mPin->Reset();
}

/**
* Overrides SetPosition in order to set positions of all components
* in the trap.
* \param pos The new position of the trap.
*/
void CTrap::SetPosition(Gdiplus::Point pos)
{
	mPin->SetPosition(pos);
	mBasket->SetPosition(pos);
	CComponent::SetPosition(pos);
}

/**
* Sets how much the pin shoule be changing in the xdirection by, this is important
* for the winch to set the speed of the pin.
* 
* \param change how much the pin should be moving in the x direction.
*/
void CTrap::SetChange(double change)
{
	mPin->SetChange(change);
}

/**
* Get the pin of the trap
*
* \returns a shared_ptr to the pin
*/
std::shared_ptr<CPin> CTrap::GetPin() const
{
	return mPin;
}
