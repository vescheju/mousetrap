/**
 * \file Mouse.cpp
 *
 * \author Justin Vesche
 *
 */

#include "pch.h"
#include "Mouse.h"
#include "Motor.h"

/// The size the mouse will be set as.
const int MouseSize = 76;

/**
 * Constructor
 * \param duration how long the mouse should move for
 * \param startPosX where the mouse starts at x
 * \param startPosY where the mouse starts at y
 * \param endPosX where the mouse ends at x
 * \param endPosY where the mouse ends at y
 */
CMouse::CMouse(double duration, int startPosX, int startPosY, int endPosX, int endPosY) : CComponent()
{
	Rectangle(0, 0, MouseSize, MouseSize);

	mDuration = duration;
	mStartPointX = startPosX;
	mStartPointY = startPosY;
	mEndPointX = endPosX;
	mEndPointY = endPosY;
	SetPosition(Gdiplus::Point(startPosX, startPosY));
	SetImage(L"images/mouse.png");

    SetOn(true);
}

/**
* Draw our mouse
* \param graphics the graphics that will be used to draw
* \param x the x location to draw at
* \param y the y location to draw at
*/
void CMouse::Draw(Gdiplus::Graphics* graphics, int x, int y)
{
	CComponent::Draw(graphics, x, y);
}

/**
* Update the movement of the mouse.
* \param elapsed the time that has passed
*/
void CMouse::Update(double elapsed)
{
    // We are moving
    mTime += elapsed;
    if (mTime < mDuration)
    {
        SetOn(true);
        // Compute position of the mouse
        double t = mTime / mDuration;
        auto positionX = mStartPointX * (1 - t) + mEndPointX * t;
        auto positionY = mStartPointY * (1 - t) + mEndPointY * t;
        SetPosition(Gdiplus::Point((int)positionX, (int)positionY));
    }
    else
    {
        SetOn(false);
        // We are past the end
        SetPosition(Gdiplus::Point((int)mEndPointX, (int)mEndPointY));
    }
}
/**
* A reset function
* Restarts the mouse location
*/
void CMouse::Reset()
{
    SetOn(true);
	SetPosition(Gdiplus::Point(mStartPointX, mStartPointY));
	mTime = 0.0;
}

/**
 * Destructor
 */
CMouse::~CMouse()
{
}

/**
* Adds a motor to be linked to the mouse
* \param motor the motor that will be linked up to the mouse.
*/
void CMouse::AddMotor(std::shared_ptr<CMotor> motor)
{
    mMotors.push_back(motor);
    motor->SetMouse(this);
}
