/**
 * \file Sink.h
 *
 * \author Justin Vesche
 *
 * The rotation driving sink class.
 */

#pragma once

class CComponent;
class CDriver;

/**
* A sink class that drives rotations of different classes.
*/
class CSink
{
public:
    ~CSink();
    CSink();
    /** \brief Copy constructor disabled */
    CSink(const CSink&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CSink&) = delete;
    
    void SetComponent(CComponent* component);

    void SetRotation(double rotation);

    CComponent* GetComponent() const;

    void SetDriver(CDriver* driver);

    /**
    * Sets the speed of how fast the sinks should be rotating.
    * 
    * \param speed The new speed of the sink.
    */
    void SetSpeed(double speed) { mSpeed = speed; }

private:
    /// The component that is connected to the sink
    CComponent* mComponent = nullptr;
    /// A pointer to the driver that is driving the sink.
    CDriver* mDriver = nullptr;
    /// default speed set to 1, but this is the speed multiplier of the rotation.
    double mSpeed = 1; 
};

