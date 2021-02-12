/**
 * \file MachineFactory2.h
 *
 * \author Justin Vesche
 *
 * A factory that creates the second machine in our project
 */

#pragma once

#include <memory>

class CActualMachine;

/**
* A class that represents our second machine
*
* Creates our machine with CreateMachine function
*/
class CMachineFactory2
{
public:
    CMachineFactory2();
    ~CMachineFactory2();

    std::shared_ptr<CActualMachine> CreateMachine();

    void AddPost(std::shared_ptr<CActualMachine> machine, int x, int height);
};

