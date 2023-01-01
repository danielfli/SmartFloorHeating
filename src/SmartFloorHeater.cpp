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
        app.EasySwitchOn(option.switchOn);
    }
    else
    {
        switch (option.runstate)
        {
        case 0:
            // app.RunOpteration();
            app.RunTest();
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

// void SmartFloorHeater::DoSomeInput()
// {
//     Input ip;
//     ip.DoConfiguration(true);
//     // ip.GetApiAccessToken(true, false);
// }

// void SmartFloorHeater::DoSomeControl()
// {
//     TwoLevelController controller(2);

//     double input = 0;
//     double actual = 0;

//     while (1)
//     {
//         std::cout << "\nSetPoint : ";
//         std::cin >> input;
//         std::cout << "\nacual Temp: ";
//         std::cin >> actual;

//         controller.SetsetPoint_W(input, actual);
//         // std::this_thread::sleep_for(std::chrono::seconds(2));
//     }
// }

} // namespace sfh