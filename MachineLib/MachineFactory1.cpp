/**
 * \file MachineFactory1.cpp
 *
 * \author Justin Vesche
 */

#include "pch.h"
#include "MachineFactory1.h"
#include "ActualMachine.h"
#include "Shape.h"
#include "Mouse.h"
#include "Motor.h"
#include "Gear.h"
#include "Trap.h"
#include "Winch.h"

using namespace std;
using namespace Gdiplus;

/**
 * Constructor
 */
CMachineFactory1::CMachineFactory1()
{
}


/**
 * Destructor
 */
CMachineFactory1::~CMachineFactory1()
{
}

/**
 * Create a machine object
 * \returns Object of type CActualMachine
 */
std::shared_ptr<CActualMachine> CMachineFactory1::CreateMachine()
{
    // Locations of stuff
    const int CheeseSize = 70;
    const int CheeseX = -73;
    const int CheeseY = 2;
    const int MouseSize = 76;

    const int MotorX = -250;
    const int MotorY = -50;
    const int WinchX = -250;

    // Gear locations. Gear 1 is the location of the motor, 
    // Gear 2 and 3 are at the same location.
    const int Gear2X = MotorX + 59;
    const int Gear2Y = -109;
    const int Gear4X = Gear2X - 79;
    const int Gear4Y = Gear2Y - 60;


	shared_ptr<CActualMachine> machine = make_shared<CActualMachine>();

    // The base
    auto base = make_shared<CShape>();
    int wid = 650;
    base->Rectangle(-wid / 2, 10, wid, 10);
    base->SetColor(Color::DarkGray);
    machine->AddComponent(base);

    // Add post that hol the 2nd and 4th gears
    // You can only just barely see the one 
    // for the 4th gear behind the motor and gears
    AddPost(machine, Gear2X, -Gear2Y + 10);
    AddPost(machine, Gear4X, -Gear4Y + 10);


    // The cheese
    auto cheese = make_shared<CShape>();
    cheese->Rectangle(0, 0, CheeseSize, CheeseSize);
    cheese->SetPosition(Point(CheeseX, CheeseY));
    cheese->SetImage(L"images/cheese.png");
    machine->AddComponent(cheese);

    // The mouse
    auto mouse = make_shared<CMouse>(2.0, 250, 0, CheeseX + CheeseSize + MouseSize / 2 - 45, 0);
    machine->AddComponent(mouse);


    // The motor
    auto motor = make_shared<CMotor>();
    motor->SetPosition(Point(MotorX, MotorY));
    machine->AddComponent(motor);

    // Tell the mouse so it can turn on this motor
    mouse->AddMotor(motor);

    // The trap
    auto trap = make_shared<CTrap>();
    trap->SetPosition(Point(0, 0));
    machine->AddComponent(trap);

    // The winch
    auto winch = make_shared<CWinch>();
    winch->SetPosition(Point(WinchX, -266 + winch->GetRadius()));
    winch->SetCableEnd(-46, -266);

    winch->SetTrap(trap);


    // The gear driven by the motor
    // Radius=30pixels, 15 teeth
    auto gear1 = make_shared<CGear>(30, 15);
    gear1->SetImage(L"images/iron.png");
    gear1->SetPosition(Point(MotorX, MotorY));
    machine->AddComponent(gear1);

    motor->GetSource()->AddSink(gear1->GetSink());





    // The second gear
    // Radius=60pixels, 35 teeth
    auto gear2 = make_shared<CGear>(60, 35);
    gear2->SetImage(L"images/hammered-copper.png");
    gear2->SetPosition(Point(Gear2X, Gear2Y));
    gear2->SetAdjust(0.01);

    

    // We add the post before the gear,
    // so it is behind it.
    machine->AddComponent(gear2);

    gear1->Drive(gear2);

    // A third gear
    auto gear3 = make_shared<CGear>(25, 15);
    gear3->SetImage(L"images/iron.png");
    gear3->SetPosition(gear2->GetPosition());
    machine->AddComponent(gear3);

    // Direct connection
    gear2->GetSource()->AddSink(gear3->GetSink());

    auto gear4 = make_shared<CGear>(80, 50);
    gear4->SetImage(L"images/steel.png");
    gear4->SetPosition(Point(Gear4X, Gear4Y));
    gear4->SetAdjust(0.005);
    machine->AddComponent(gear4);

    gear3->Drive(gear4);

    // Gear 5: Radius=21pixels, 13 teeth
    auto gear5 = make_shared<CGear>(21, 13);
    gear5->SetImage(L"images/iron.png");
    gear5->SetPosition(gear4->GetPosition());
    machine->AddComponent(gear5);

    // Direct connection
    gear4->GetSource()->AddSink(gear5->GetSink());

    auto gear6 = make_shared<CGear>(50, 40);
    gear6->SetImage(L"images/hammered-copper.png");
    gear6->SetPosition(winch->GetPosition());
    gear6->SetAdjust(0.013);
    machine->AddComponent(gear6);

    gear5->Drive(gear6);
    gear6->GetSource()->AddSink(winch->GetSink());

    machine->AddComponent(winch);
   
    // Flag that is driven by the winch as it moves
    auto flag = make_shared<CShape>();
    flag->AddPoint(0, 0);
    flag->AddPoint(0, -120);
    flag->AddPoint(60, -120);
    flag->AddPoint(60, 0);
    flag->SetImage(L"images/mouse-flag.png");
    flag->SetPosition(winch->GetPosition());
    machine->AddComponent(flag);
    winch->GetSource()->AddSink(flag->GetSink());

	return machine;
}



/**
 * Add a post.
 *
 * Since I found I liked adding posts, I decided to create
 * a function to do that with the post and base so I could
 * add a post with only one line of code.
 *
 * \param machine Machine we are adding the post to.
 * \param x X location for the post
 * \param height Height of the post
 */
void CMachineFactory1::AddPost(std::shared_ptr<CActualMachine> machine, int x, int height)
{
    // The post itself
    auto post = make_shared<CShape>();
    post->Rectangle(-5, 0, 10, height);
    post->SetPosition(Point(x, 0));
    post->SetImage(L"images/post.png");
    machine->AddComponent(post);

    // The post base. It's a square image that
    // is 4 times as wide as the post image
    auto base = make_shared<CShape>();
    base->Rectangle(-20, 0, 40, 40);
    base->SetPosition(Point(x, 0));
    base->SetImage(L"images/post-base.png");
    machine->AddComponent(base);
}