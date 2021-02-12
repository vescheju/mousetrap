/**
 * \file Component.cpp
 *
 * \author Justin Vesche
 */

#include "pch.h"
#include "Component.h"

/**
* Draw our item
* \param graphics The graphics context to draw on
* \param x the x location to draw at
* \param y the y location to draw at
*/
void CComponent::Draw(Gdiplus::Graphics* graphics, int x, int y)
{
    CPolygon::DrawPolygon(graphics, mPosition.X+x, mPosition.Y+y);
}

/// deconstructor
CComponent::~CComponent()
{

}

/// Constructor
CComponent::CComponent()
{

}
