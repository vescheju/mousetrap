/**
 * \file Shape.cpp
 *
 * \author Justin Vesche
 */

#include "pch.h"
#include "Shape.h"


/**
* Constructor
*/
CShape::CShape() : CComponent()
{
	mSink.SetComponent(this);
}

/**
* Draw our item
* \param graphics The graphics context to draw on
* \param x the x location to draw at
* \param y the y location to draw at
*/
void CShape::Draw(Gdiplus::Graphics* graphics, int x, int y)
{
	CComponent::Draw(graphics, x, y);
}

/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CShape::Update(double elapsed)
{

}

/**
* A reset function
* Restarts the shape location
*/
void CShape::Reset()
{
	SetRotation(0);
}

/**
 * Destructor
 */
CShape::~CShape()
{
}

/** Override the SetRotation function to downstream rotations
* \param rotation the rotation to be set.
*/
void CShape::SetRotation(double rotation)
{
	CPolygon::SetRotation(rotation);
}
