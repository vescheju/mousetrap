/**
 * \file MachineFactory.cpp
 *
 * \author Charles Owen
 *
 * You are allowed to change this file.
 */

#include "pch.h"
#include "MachineFactory.h"
#include "Machine.h"
#include "MachineInterpret.h"


using namespace std;

/**
 * Constructor
 */
CMachineFactory::CMachineFactory()
{
}


/**
 * Destructor
 */
CMachineFactory::~CMachineFactory()
{
}


/**
 * Create a machine object
 * \returns Object of type CMachine
 */
std::shared_ptr<CMachine> CMachineFactory::CreateMachine()
{
    return make_shared<CMachineInterpret>();
}

