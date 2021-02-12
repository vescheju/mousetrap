/**
 * \file Motor.h
 *
 * \author Justin Vesche
 *
 * Class that represents the motor and its driving factor.
 *
 */

#pragma once
#include "Component.h"
#include<memory>
#include "Driver.h"

class CPolygon;
class CMouse;


/**
* Class that represents the motor and its driving factor.
*
* The foundation for movement of the mouse trap.
*/
class CMotor : public CComponent
{
public:
    CMotor();

    virtual ~CMotor();

    /** \brief Copy constructor disabled */
    CMotor(const CMotor&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CMotor&) = delete;

    virtual void Draw(Gdiplus::Graphics* graphics, int x, int y);

    virtual void Update(double elapsed) override;

    virtual void Reset() override;

    /**
    * Set the speed of the motor
    * \param speed the speed we will set the motor as.
    */
    void SetSpeed(double speed) { mSpeed = speed; }

    void SetMouse(CMouse* mouse);

    CMouse* GetMouse() const;

    /** Get a pointer to the source object
    * \returns Pointer to CDriver object
    */
    CDriver* GetSource() { return &mSource; }
    

private:
    /// The speed the motor will rotate at
    double mSpeed = 1.0;
    /// A polygon of the base;
    std::shared_ptr<CPolygon> mBase;
    /// A pointer to the mouse that will drive the motor.
    CMouse* mMouse;
    /// Rotation source for this component
    CDriver mSource;

};

