/**
 * \file Component.h
 *
 * \author Justin Vesche
 *
 * A class that represents components. Abstract and derived from polygon.
 */

#pragma once
#include <string>
#include "Polygon.h"


/**
* A class that represents components.
*
* Abstract and derived from polygon.
*/
class CComponent : public CPolygon
{
public:
	
	virtual void Draw(Gdiplus::Graphics* graphics, int x, int y);

	/** Handle updates for animation
	* \param elapsed The time since the last update
	*/
	virtual void Update(double elapsed) = 0;

	/** \brief Copy constructor disabled */
	CComponent(const CComponent&) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CComponent&) = delete;

	/** Set the componets position
	 * \param pos The new componets position*/
	virtual void SetPosition(Gdiplus::Point pos) { mPosition = pos; }

	/** Get the componets position
	 * \returns The componets position*/
	Gdiplus::Point GetPosition() const { return mPosition; }


	/** Set the componets move boolean
	 * \param on Set if the component should move*/
	void SetOn(bool on) { mOn = on; }

	/** Get the componets boolean movement
	 * \returns Boolean if should move or not*/
	bool GetOn() const { return mOn; }

	virtual ~CComponent();

	/** A function soon to be overrided. resets everything.
	 */
	virtual void Reset() = 0;

protected:
	CComponent();

private:
	/// Point represeneting the position of the component
	Gdiplus::Point mPosition = Gdiplus::Point(0,0);
	/// Boolean to check if the component should be moving or not.
	bool mOn = false;
};

