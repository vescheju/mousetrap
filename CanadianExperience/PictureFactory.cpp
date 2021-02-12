/**
 * \file PictureFactory.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include "PictureFactory.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "ImageDrawable.h"
#include "Adapter.h"

using namespace std;
using namespace Gdiplus;

CPictureFactory::CPictureFactory()
{
}


CPictureFactory::~CPictureFactory()
{
}


/*! Factory method to create a new picture.
* \returns The created picture
*/
std::shared_ptr<CPicture> CPictureFactory::Create()
{
    shared_ptr<CPicture> picture = make_shared<CPicture>();

    // Create the background and add it
    auto background = make_shared<CActor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(Point(-100, 0));
    auto backgroundI = make_shared<CImageDrawable>(L"Background", L"images/Background.png");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    // Create the first trap
    auto machineRoot = make_shared<CActor>(L"machine root");
    
    auto machine1 = make_shared<CAdapter>(L"machine1");
    picture->SetMachine1(machine1);
    machine1->SetPosition(Point(675, 300));
    machineRoot->AddDrawable(machine1);
    machineRoot->SetRoot(machine1);
    picture->AddActor(machineRoot);

    // Create the second trap
    auto machineRoot2 = make_shared<CActor>(L"machine root2");
    auto machine2 = make_shared<CAdapter>(L"machine2");
    picture->SetMachine2(machine2);
    machine2->SetMachineNumber(2);
    machine2->SetPosition(Point(275, 450));
    machineRoot2->AddDrawable(machine2);
    machineRoot2->SetRoot(machine2);
    picture->AddActor(machineRoot2);



    // Create and add Harold
    CHaroldFactory factory;
    auto harold = factory.Create();

    // This is where Harold will start out.
    harold->SetPosition(Point(750, 500));

    picture->AddActor(harold);

    // Create and add Sparty
    CSpartyFactory sfactory;
    auto sparty = sfactory.Create();

    sparty->SetPosition(Point(520, 500));
    picture->AddActor(sparty);

    return picture;
}
