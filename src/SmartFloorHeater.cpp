#include "../include/smartfloorheading/SmartFloorHeater.hpp"
#include "Output.hpp"
#include <iostream>
#include <thread>
// #include <chrono>
namespace sfh
{

SmartFloorHeater::SmartFloorHeater()
{
}

SmartFloorHeater::~SmartFloorHeater()
{
}

void SmartFloorHeater::DoSome()
{
    unsigned int distr = 5;
    Output out{distr};
    auto switches = out.GetSwitches();
    // out.SwitchAllOn();
    int cout = 10;
    unsigned int numSwitch = 0;
    while (cout > 0)
    {
        cout--;
        out.TurnOn(switches[0]);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        out.TurnOff(switches[0]);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    out.SwitchAllOn();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    out.SwitchAllOff();

    std::cout << "small checkout menu\n";
    std::cout << "Enter a number 0 - X to switch on for 2 sec (break with 99)- ";
    while (true)
    {
        std::cout << "number: ";
        std::cin >> numSwitch;
        if (numSwitch == 99)
        {
            break;
        }
        else if (numSwitch < distr)
        {
            out.TurnOn(switches[numSwitch]);
            std::this_thread::sleep_for(std::chrono::seconds(2));
            out.TurnOff(switches[numSwitch]);
        }
    }
}

} // namespace sfh