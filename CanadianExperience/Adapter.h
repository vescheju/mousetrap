/**
 * \file Adapter.h
 *
 * \author Justin Vesche
 * 
 * Class that adapats our machines to CanadianExperience
 */

#pragma once
#include "Drawable.h"
#include <memory>
#include "Machine.h"
#include "MachineFactory.h"
#include "MachineDlg.h"


/**
* Class that adapats our machines to CanadianExperience
*
* Allows the machines to be used in our main program.
*/
class CAdapter : public CDrawable
{
public:

    /** \brief Default constructor disabled */
    CAdapter() = delete;
    /** \brief Copy constructor disabled */
    CAdapter(const CAdapter&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CAdapter&) = delete;

    ~CAdapter();

    CAdapter(const std::wstring& name);

	virtual void Draw(Gdiplus::Graphics* graphics) override;

	virtual bool HitTest(Gdiplus::Point position) override;

    void SetMachineNumber(int num);
    
    void MachineImp();

    void SetFrame(int num);

private:
	/// A shared_ptr to our machine.
	std::shared_ptr<CMachine> mMachine;

};

