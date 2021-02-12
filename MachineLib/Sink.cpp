/**
 * \file Sink.cpp
 *
 * \author Justin Vesche
 */

#include "pch.h"
#include "Sink.h"
#include "Component.h"
#include "Driver.h"	

/**
* Constructor
*/
CSink::~CSink()
{
}

/**
 * Destructor
 */
CSink::CSink()
{
}

/**
* Sets the component that will be a sink.
*
* \param component A pointer to what component will be a sink.
*/
void CSink::SetComponent(CComponent* component)
{
	mComponent = component;
}

/**
* Uses speed to move each sink. This is called by driver to slow down gears.
*
* \param rotation the amount the sink should rotate with speed applied.
*/
void CSink::SetRotation(double rotation)
{
	if (mComponent != nullptr)
	{
		mComponent->SetRotation(rotation * mSpeed);
	}
}

/**
* Getter for the component held by the sink.
*
* \returns A pointer to the component, that is a sink.
*/
CComponent* CSink::GetComponent() const
{
	return mComponent;
}

/**
* Sets what will be driving the current sink.
* 
* \param driver a pointer to the driver that will drive it.
*/
void CSink::SetDriver(CDriver* driver)
{
	mDriver = driver;
}
