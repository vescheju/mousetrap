/**
 * \file Mouse.h
 *
 * \author Justin Vesche
 *
 * A class that represents the mouse
 */

#pragma once
#include "Component.h"
#include <memory>
#include<vector>

class CMotor;

 /**
 * A class that represents a mouse.
 *
 * The mouse is the first object to move in the trap.
 */
class CMouse : public CComponent
{
public:
    /** \brief Default constructor disabled */
    CMouse() = delete;
    /** \brief Copy constructor disabled */
    CMouse(const CMouse&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CMouse&) = delete;

    CMouse(double duration, int startPosX, int startPosY, int endPosX, int endPosY);

    virtual void Draw(Gdiplus::Graphics* graphics, int x, int y);

    virtual void Update(double elapsed) override;

    virtual void Reset() override;

    virtual ~CMouse();

    void AddMotor(std::shared_ptr<CMotor> motor);


private:
    /// The initial y location of the mouse
    int mStartPointY;
    /// the intial x location of the mouse
    int mStartPointX;
    /// The end y location of the mouse
    int mEndPointY;
    /// the end x location of the mouse
    int mEndPointX;
    /// the duration of the mouse movement
    double mDuration;
    /// how long the mouse has been moving for
    double mTime = 0.0;
    /// collection of motors to be turned
    std::vector<std::shared_ptr<CMotor> > mMotors;

};

