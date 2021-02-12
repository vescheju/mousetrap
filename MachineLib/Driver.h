/**
 * \file Driver.h
 *
 * \author Justin Vesche
 *
 * The rotation driving class.
 */

#pragma once
#include<vector>
class CSink;

 /**
 * The rotation driving class.
 */
class CDriver
{
public:
    /// Copy constructor (disabled)
    CDriver(const CDriver&) = delete;

    /// Assignment operator (disabled)
    void operator=(const CDriver&) = delete;

    CDriver();
    ~CDriver();

    void AddSink(CSink* sink);

    void SetRotation(double rotation);

private:
    /// A vector of sinks, driven by driver.
    std::vector<CSink*> mSinks;
};

