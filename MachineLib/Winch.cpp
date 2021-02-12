/**
 * \file Winch.cpp
 *
 * \author Justin Vesche
 */

#include "pch.h"
#include "Winch.h"
#include "Trap.h"


/// Value of PI
const double M_PI = 3.1415;

using namespace Gdiplus;

/**
* Constructor
*/
CWinch::CWinch() : CComponent()
{

	CenteredSquare(mRadius * 2);
	SetImage(L"images/drum.png");

	mSink.SetComponent(this);

}

/**
 * Destructor
 */
CWinch::~CWinch()
{
}

/**
* Draw our winch and the string
* \param graphics The graphics context to draw on
* \param x the x location to draw at
* \param y the y location to draw at
*/
void CWinch::Draw(Gdiplus::Graphics* graphics, int x, int y)
{
	Pen pen(Color(142, 80, 60), 4);
	auto pos = GetPosition();
	// Smooth out the wire
	auto saveSM = graphics->GetSmoothingMode();
	graphics->SetSmoothingMode(SmoothingMode::SmoothingModeHighQuality);
	// Find the cable x and y difference
	double xDifference = (double)mCableEnd.X() - (double)pos.X;
	double yDifference = (double)mCableEnd.Y() - (double)pos.Y;
	// use formulas
	double theta = atan2(yDifference, xDifference);

	double distance = sqrt((double)(xDifference * xDifference) + (yDifference * yDifference));
	double phi = asin(double(mRadius) / distance);
	double b = theta - phi + M_PI / 2.0;

	CVector tangent(double(mRadius) * cos(b), double(-mRadius) * sin(b));

	CVector point1(pos.X, pos.Y);

	tangent = tangent + point1;

	// Draw a partial line
    // First, how far is it from the tangent point to the cable end?
	mD = tangent.Distance(mCableEnd);
	// Check if cablelength is set
	if (int(mCableLength) == 0)
	{
		mCableLength = mD;
	}

	// What percentage of the line is still outstanding?
	double t = mCableLength / mD;

	// Draw just that much
	auto f = t;

	auto drawPoint = tangent + (mCableEnd - tangent) * t;

	// draw our line now
	graphics->DrawLine(&pen, int(tangent.X() + x) - 4, int(tangent.Y() + y), int(x + drawPoint.X()), int(y + drawPoint.Y()));
	CComponent::Draw(graphics, x, y);
	
	graphics->SetSmoothingMode(saveSM);

}

/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CWinch::Update(double elapsed)
{
}

/**
* A reset function
* Restarts the string, trap, and rotation
*/
void CWinch::Reset()
{
	CComponent::SetRotation(0);
	auto pos = GetPosition();
	// Similar calculation above, only this time for the reset, with minor differences
	double xDifference = (double)mCableEnd.X() - (double)pos.X;
	double yDifference = (double)mCableEnd.Y() - (double)pos.Y;

	double theta = atan2(yDifference, xDifference);

	double distance = sqrt((double)(xDifference * xDifference) + (yDifference * yDifference));
	double phi = asin(double(mRadius) / distance);
	double b = theta - phi + M_PI / 2.0;

	CVector tangent(double(mRadius) * cos(b), double(-mRadius) * sin(b));

	CVector point1(pos.X, pos.Y);

	tangent = tangent + point1;

	mD = tangent.Distance(mCableEnd);
	// Set the length of the cable to the distance between the tangent and the end of the cable
	mCableLength = mD;

	// reset the trap
	mTrap->Reset();
}

/**
* Gets the radius of the trap
* \returns The radius.
*/
int CWinch::GetRadius()
{
	return mRadius;
}




/** Override the SetRotation function to downstream rotations
* \param rotation the rotation to be set.
*/
void CWinch::SetRotation(double rotation)
{
	// Rotate the winch if needed
	if (rotation != 0 && !mTrap->GetPin()->GetEnd())
	{
		// Change the rope to the dependence of rotation depends on circle circumfrance and rotation amount.
		mCableLength -= abs((GetRotation()-rotation)*GetRadius()*2*M_PI);
		CPolygon::SetRotation(rotation);
		mSource.SetRotation(rotation);
		mTrap->SetChange(mD - mCableLength);
	}
	
		
}

/** 
* Set the endpoint of our cable.
* \param x The x spot of the endpoint
* \param y The y spot of the endpoint
*/
void CWinch::SetCableEnd(int x, int y)
{
	mCableEnd = CVector(x, y);

	mCableLength = 0.0;

}

/**
* Setting the pointer mTrap.
* \param trap the trap that will be changed by the winch
*/
void CWinch::SetTrap(std::shared_ptr<CTrap> trap)
{
	mTrap = trap;
}


