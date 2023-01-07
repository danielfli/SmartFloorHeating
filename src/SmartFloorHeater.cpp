#include "../include/smartfloorheating/SmartFloorHeater.hpp"
#include "Builder.hpp"
namespace sfh
{
SmartFloorHeater::SmartFloorHeater()
{
}

SmartFloorHeater &SmartFloorHeater::GetInstance()
{
    static SmartFloorHeater _instance;

    return _instance;
}

void SmartFloorHeater::Execute(SFHOption &option)
{
    Builder app(option.verbose);
    if (option.switchOn != 99)
    {
        // app.EasySwitchOn(option.switchOn);
    }
    else
    {
        switch (option.runstate)
        {
        case 0:
            app.RunOpteration(option.percent);
            break;
        case 10:
            app.RunSimualtion();
            break;
        case 20:
            app.RunMaunal();
            break;
        }
    }
}
} // namespace sfh