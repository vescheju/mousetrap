/**
 * \file Gear.h
 *
 * \author Justin Vesche
 *
 * The rotation driving class.
 */

#pragma once
#include "Component.h"
#include "Driver.h"
#include "Sink.h"
 /**
 * A class that represents Gears.
 *
 * Derived from component
 */
class CGear : public CComponent
{
public:
    CGear(int radius, int teeth);
    ~CGear();
    /** \brief Copy constructor disabled */
    CGear(const CGear&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CGear&) = delete;

    virtual void Draw(Gdiplus::Graphics* graphics, int x, int y);

    virtual void Update(double elapsed) override;

    virtual void Reset() override;

    virtual void SetRotation(double rotation) override;

    /** Get a pointer to the source object
    * \returns Pointer to CDriver object*/
    CDriver* GetSource() { return &mSource; }

    /**
    * Get the sink connected to shape.
    *
    * \returns a pointer to the sink.
    */
    CSink* GetSink() { return &mSink; }

    void Drive(std::shared_ptr<CGear> gear);

    /** Get the number of teeth of the gear
    * \returns int of the amount of teeth*/
    int GetNumTeeth() const { return mTeeth; }

    void SetAdjust(double adj);



private:
    /// The number of teeth the gear has
    int mTeeth;
    /// The radius of the gear
    int mRadius;
    /// Rotation source for this component
    CDriver mSource;
    CSink mSink; ///< The rotation sink for this component
    /// The amount the gear should adjust to
    double mAdjustment = 0.0;


};

