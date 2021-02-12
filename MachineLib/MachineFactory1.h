/**
 * \file MachineFactory1.h
 *
 * \author Justin Vesche
 *
 * A factory that creates the first machine in our project
 */

#pragma once
#include <memory>

class CActualMachine;

/**
* A class that represents our first machine
*
* Creates our machine with CreateMachine function
*/
class CMachineFactory1
{
public:
    CMachineFactory1();
    ~CMachineFactory1();

    std::shared_ptr<CActualMachine> CreateMachine();

    void AddPost(std::shared_ptr<CActualMachine> machine, int x, int height);
};

