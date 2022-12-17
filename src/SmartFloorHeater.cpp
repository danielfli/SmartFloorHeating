#include "../include/smartfloorheading/SmartFloorHeater.hpp"
#include "Output.hpp"
#include <thread>
#include <iostream>
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
    Output out{5};

    out.SwitchAllOn();
    while (true)
    {
        out.TurnOn(out.GetSwitches()[2]);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        out.TurnOff(out.GetSwitches()[2]);
    
    }
}

} // namespace sfh