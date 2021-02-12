/**
 * \file Shape.h
 *
 * \author Justin Vesche
 *
 * A basic shape function that can represent polygons or pictures
 * that can have animations.
 */

#pragma once
#include "Component.h"
#include "Sink.h"

 /**
  * A basic shape function that can represent polygons or pictures
  * that can have animations.
  */
class CShape : public CComponent
{
public:
    CShape();

    /** \brief Copy constructor disabled */
    CShape(const CShape&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CShape&) = delete;

    virtual void Draw(Gdiplus::Graphics* graphics, int x, int y);

    virtual void Update(double elapsed) override;

    virtual void Reset() override;
    
    virtual ~CShape();

    virtual void SetRotation(double rotation) override;

    /** 
    * Get the sink connected to shape.
    * 
    * \returns a pointer to the sink.
    */
    CSink* GetSink() { return &mSink; }

private:
    CSink mSink; ///< The rotation sink for this component

};

