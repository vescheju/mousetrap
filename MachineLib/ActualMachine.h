/**
 * \file ActualMachine.h
 *
 * \author Justin Vesche
 *
 * Class that represents each machine as a whole.
 *
 */

#pragma once
#include<memory>
#include<vector>
#include"Component.h"

 /**
  * Class that represents each machine as a whole.
  *
  * This class holds a collection of components that 
  * make up each machine.
  */
class CActualMachine
{
public:
    void Update(double elapsed);

    void Draw(Gdiplus::Graphics* graphics);

    void AddComponent(std::shared_ptr<CComponent> component);

    void Reset();

    CActualMachine();

    ~CActualMachine();

    /**
    * Set the machine number
    * \param machine An integer number. Each integer makes a different machine
    */
    void SetMachine(int machine) { mMachine = machine; }

    /**
    * Get the current machine number
    * \return Machine number
    */
    int GetMachine() const { return mMachine; }

    /**
    * Get the current frame 
    * \return the current frame
    */
    int GetFrame() const { return mFrame; }

    /**
    * Set the frame
    * \param frame the frame to be set.
    */
    void SetFrame(int frame) { mFrame = frame; }

    /**
    * Set the location
    * \param pos the position to set
    */
    void SetLocation(Gdiplus::Point pos) { mX = pos.X; mY = pos.Y; }




private:
    int mX = 0;     ///< Machine X location
    int mY = 0;     ///< Machine Y location
    int mFrame = 0; ///< Current frame
    int mMachine = 1;  ///< Machine number

   /// the collection of compents for the machine
    std::vector<std::shared_ptr<CComponent> > mComponents;
};

