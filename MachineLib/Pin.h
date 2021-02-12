/**
 * \file Pin.h
 *
 * \author Justin Vesche
 *
 * A class that represents the Pin of the trap.
 */

#pragma once
#include "Component.h"

/**
* A class that represents the Pin of the trap.
* Moves in the x-direction with the winch.
*/
class CPin : public CComponent
{
public:

    CPin();
    ~CPin();

    /** \brief Copy constructor disabled */
    CPin(const CPin&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CPin&) = delete;

    virtual void Draw(Gdiplus::Graphics* graphics, int x, int y);

    virtual void Update(double elapsed) override;

    virtual void Reset() override;

    virtual void SetPosition(Gdiplus::Point pos);

    /**
    * Get the starting point of the pin
    *
    * \returns the starting point of the pin.
    */
    Gdiplus::Point GetStart() { return mStartPositionX; }

    /**
    * Gets a boolean to check if the pin is at the end of the trap.
    *
    * \returns a boolean to check for the end.
    */
    bool GetEnd() const { return mEnd; }

    /**
    * Sets if the a boolean if the pin is at end or not
    *
    * \param end a boolean to set mEnd
    */
    void SetEnd(bool end) {mEnd = end; }

    /**
    * Sets mChange, or how much the pin should move.
    *
    * \param change how much the pin should be moving, similar to a speed.
    */
    void SetChange(double change) { mChange = change; }
private:
    /// A point of where the pin is currenctly located
    Gdiplus::Point mPositionX;
    /// A point of where the pin starts
    Gdiplus::Point mStartPositionX;
    /// A boolean to check if the pin should stop moving
    bool mEnd = false;
    /// How much the pin should be moving in the x direction
    double mChange = 0.0;

};

