#include "../include/smartfloorheading/SmartFloorHeater.hpp"
#include "Output.hpp"
#include <thread>  
#include <chrono> 
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

    std::this_thread::sleep_for (std::chrono::seconds(1));
    // auto test = ;
    out.TurnOn(out.GetSwitches()[2]);
}

} // namespace sfh