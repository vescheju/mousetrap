/**
 * \file Gear.cpp
 *
 * \author Justin Vesche
 */

#include "pch.h"
#include "Gear.h"
#include "Const.h"

const double ToothDepth = 5;     ///< Depth of a tooth in pixels
const double ToothWidth = 0.33;  ///< Width of a tooth at the top as fraction of tooth pitch
const double ToothSlope = 0.1;   ///< Fraction of pitch where the tooth slopes up or down

/**
* Constructor
* \param radius the radius of the gear
* \param teeth how much teeth the gear will have
*/
CGear::CGear(int radius, int teeth) : CComponent()
{
    mRadius = radius; 
    mTeeth = teeth; 

    // Where the tooth starts in the arc
    double toothStart = 1.0 - ToothWidth - ToothSlope * 2;
    double innerRadius = mRadius - ToothDepth;
    // Set the teeth of the gear
    for (int t = 0; t < mTeeth; t++)
    {
        double angle1 = double(t) / double(mTeeth) * CConst::PI2;
        double angle2 = double(t + toothStart) / double(mTeeth) * CConst::PI2;
        double angle3 = double(t + toothStart + ToothSlope) / double(mTeeth) * CConst::PI2;
        double angle4 = double(t + toothStart + ToothSlope + ToothWidth) / double(mTeeth) * CConst::PI2;
        double angle5 = double(t + toothStart + ToothSlope * 2 + ToothWidth) / double(mTeeth) * CConst::PI2;

        AddPoint(innerRadius * cos(angle1), innerRadius * sin(angle1));
        AddPoint(innerRadius * cos(angle2), innerRadius * sin(angle2));
        AddPoint(mRadius * cos(angle3), mRadius * sin(angle3));
        AddPoint(mRadius * cos(angle4), mRadius * sin(angle4));
        AddPoint(innerRadius * cos(angle5), innerRadius * sin(angle5));

    }
    mSink.SetComponent(this);
}

/**
 * Destructor
 */
CGear::~CGear()
{
}

/**
* Draw our item
* \param graphics The graphics context to draw on
* \param x the x location to draw at
* \param y the y location to draw at
*/
void CGear::Draw(Gdiplus::Graphics* graphics, int x, int y)
{
    CComponent::Draw(graphics, x, y);
}

/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CGear::Update(double elapsed)
{
}

/** A function that resets the gears.
*/
void CGear::Reset()
{
    CComponent::SetRotation(mAdjustment);
}

/** Override the SetRotation function to downstream rotations
* \param rotation the rotation to be set.
*/
void CGear::SetRotation(double rotation)
{
    CComponent::SetRotation(rotation + mAdjustment);
    mSource.SetRotation(rotation);
}

/** A function that tells the gear what other gears it will be driving
* \param gear the gear that the calling gear will be driving
*/
void CGear::Drive(std::shared_ptr<CGear> gear)
{
    mSource.AddSink(gear->GetSink());

    gear->GetSink()->SetSpeed(-(double)GetNumTeeth() / (double)gear->GetNumTeeth());
}

/** A function that tells slightly rotates the gears to adjust
* \param adj the amount to adjust to.
*/
void CGear::SetAdjust(double adj)
{
    CComponent::SetRotation(adj);
    mAdjustment = adj;
}




