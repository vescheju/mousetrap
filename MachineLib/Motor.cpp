/**
 * \file Motor.cpp
 *
 * \author Justin Vesche
 */

#include "pch.h"
#include "Motor.h"
#include "Mouse.h"

/// The base size of the motor.
const int BaseSize = 100;
/// The size of the moving part of the motor.
const int MotorSize = 30;

/**
 * Constructor
 */
CMotor::CMotor() : CComponent()
{
	// Sets the imaging and squaring of the components.
	mBase = std::make_shared<CPolygon>();
	mBase->CenteredSquare(BaseSize);
	CenteredSquare(MotorSize);
	mBase->SetImage(L"images/motor2.png");
	SetImage(L"images/shaft.png");
}

/**
 * Destructor
 */
CMotor::~CMotor()
{
}

/**
* Draw our motor 
* \param graphics the graphics that will be used to draw
* \param x the x location to draw at
* \param y the y location to draw at
*/
void CMotor::Draw(Gdiplus::Graphics* graphics, int x, int y)
{
	Gdiplus::Point pos = GetPosition();
	mBase->DrawPolygon(graphics, pos.X + x, pos.Y + y);

	CComponent::Draw(graphics, x, y);

}

/**
* Update the motor, only to spin of the mouse hits the cheese.
* \param elapsed the time that has passed
*/
void CMotor::Update(double elapsed)
{
	if (!mMouse->GetOn())
	{
		auto rotation = GetRotation();
		rotation += elapsed * mSpeed;
		SetRotation(rotation);

		mSource.SetRotation(rotation);
	}
}

/**
* A reset function
* Restarts the rotation of the motor.
*/
void CMotor::Reset()
{
	SetRotation(0);
}

/**
* Set the mouse linked to the motor
* \param mouse the mouse to be set
*/
void CMotor::SetMouse(CMouse* mouse)
{
	mMouse = mouse;
}

/**
* Gets the pointer to the mouse
* \returns a pointer to the mouse
*/
CMouse* CMotor::GetMouse() const
{
	return mMouse;
}




