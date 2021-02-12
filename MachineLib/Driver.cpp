/**
 * \file Driver.cpp
 *
 * \author Justin Vesche
 */

#include "pch.h"
#include "Driver.h"
#include "Sink.h"

/**
* Constructor
*/
CDriver::CDriver()
{
}

/**
 * Destructor
 */
CDriver::~CDriver()
{
}

/**
* Add a sink to our vector of sinks.
* \param sink a sink that will be added to our vector
*/
void CDriver::AddSink(CSink* sink)
{
	mSinks.push_back(sink);
	sink->SetDriver(this);
}

/** SetRotation function to downstream rotations
* \param rotation the rotation to be set.
*/
void CDriver::SetRotation(double rotation)
{
	for (auto item : mSinks)
	{
		item->SetRotation(rotation);
	}
}
