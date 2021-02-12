/**
 * \file Trap.h
 *
 * \author Justin Vesche
 *
 * A class that represents the trap.
 */


#pragma once
#include "Component.h"
#include "Basket.h"
#include "Pin.h"

 /**
 * A class that represents the trap.
 *
 * The trap holds the components of the pin, the base, and the basket.
 * Using functions to update them.
 */
class CTrap : public CComponent
{
public:
    /** \brief Copy constructor disabled */
    CTrap(const CTrap&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CTrap&) = delete;

    ~CTrap();

    CTrap();

    virtual void Draw(Gdiplus::Graphics* graphics, int x, int y);

    virtual void Update(double elapsed) override;

    virtual void Reset() override;

    virtual void SetPosition(Gdiplus::Point pos);

    void SetChange(double change);

    std::shared_ptr<CPin> GetPin() const;
private:
    /// A polygon of the front trap;
    std::shared_ptr<CPolygon> mFront;

    /// A pin of the front trap;
    std::shared_ptr<CPin> mPin;

    /// A basket of the front trap;
    std::shared_ptr<CBasket> mBasket;



};

