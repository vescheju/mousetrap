/**
 * \file Basket.h
 *
 * \author Justin Vesche
 *
 * Class that represents the basket
 *
 */

#pragma once
#include "Component.h"

/**
* Class that represents the basket
*
* Makes up for the basket in the trap.
* for the machine.
*/
class CBasket : public CComponent
{
public:
    /** \brief Copy constructor disabled */
    CBasket(const CBasket&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CBasket&) = delete;

    ~CBasket();

    CBasket();

    virtual void Draw(Gdiplus::Graphics* graphics, int x, int y);

    virtual void Update(double elapsed) override;

    virtual void Reset() override;

    virtual void SetPosition(Gdiplus::Point pos);




private:
    /// The starting location of the basket, to reset.
    int mStartPosY;
};

