/**
 * \file MachineInterpret.h
 *
 * \author Justin Vesche
 *
 * Class that represents a machine derived from CMachine.
 *
 */

#pragma once
#include "Machine.h"
#include "ActualMachine.h"
#include <memory>


/**
* Class that represents a machine derived from CMachine.
*
* Holds an actual machine pointer and modifies it.
*/
class CMachineInterpret : public CMachine
{
public:
    /// Constructor
    CMachineInterpret();

    /// Destructor
    virtual ~CMachineInterpret() {}

    /// Copy constructor/disabled
    CMachineInterpret(const CMachineInterpret&) = delete;

    /// Assignment operator/disabled
    void operator=(const  CMachineInterpret&) = delete;

    /**
    * Set the position for the root of the machine
    * \param x X location (pixels)
    * \param y Y location (pixels)
    */
    virtual void SetLocation(int x, int y);

    /**
    * Draw the machine at the currently specified location
    * \param graphics GDI+ Graphics object
    */
    virtual void DrawMachine(Gdiplus::Graphics* graphics);

    /**
    * Set the current machine animation frame
    * \param frame Frame number
    */
    virtual void SetMachineFrame(int frame);

    /**
    * Set the machine number
    * \param machine An integer number. Each number makes a different machine
    */
    virtual void SetMachineNumber(int machine);

    /**
     * Get the current machine number
     * \return Machine number integer
     */
    virtual int GetMachineNumber();


private:
   /// This stores the actual machine, or the collection of parts.
    std::shared_ptr<CActualMachine> mMachine;

};

