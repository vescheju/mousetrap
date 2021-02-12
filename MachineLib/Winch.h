/**
 * \file Winch.h
 *
 * \author Justin Vesche
 *
 * A class that represents the winch for the trap.
 */

#pragma once
#include "Component.h"
#include "Sink.h"
#include "Driver.h"
#include "Vector.h"

class CTrap;

/**
* A class that represents the winch for the trap.
* 
* Uses a string to pull the pin and set the trap.
*/
class CWinch : public CComponent
{
public:

    /** \brief Copy constructor disabled */
    CWinch(const CWinch&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CWinch&) = delete;

    CWinch();
    ~CWinch();

    virtual void Draw(Gdiplus::Graphics* graphics, int x, int y);

    virtual void Update(double elapsed) override;

    virtual void Reset() override;

    int GetRadius();


    virtual void SetRotation(double rotation);

    virtual void SetCableEnd(int x, int y);

    /**
    * Get the sink connected to shape.
    *
    * \returns a pointer to the sink.
    */
    CSink* GetSink() { return &mSink; }


    /** Get a pointer to the source object
     *\returns Pointer to CDriver object
     */
    CDriver* GetSource() { return &mSource; }

    void SetTrap(std::shared_ptr<CTrap> trap);

    
    
private:
    /// Where on the screen the cable is going to end.
    CVector mCableEnd;
    /// The current length of the cable
    double mCableLength = 0.0;
    /// Distance between the tangent and end of cable, used for calculations
    double mD = 0.0;

    CSink mSink; ///< The rotation sink for this component

    /// Rotation source for this component
    CDriver mSource;
    /// The radius of the winch
    int mRadius = 35;
    /// a pointer to the trap, helps pull the pin.
    std::shared_ptr<CTrap> mTrap;
};

