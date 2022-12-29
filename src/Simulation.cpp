#include "Simulation.hpp"
#include <chrono>
#include <iostream>
#include <thread>

namespace sfh
{

namespace utils
{
int ConvertOutput(int switcher)
{
    int result = 0;
    // Convert to 1 - xx
    if (switcher < 0)
    {
        result = switcher + 1;
    }
    else
    {
        result = switcher - 1;
    }
    return result;
}
} // namespace utils

Simulation::Simulation(const HeatingConstruction heater, const int Switcher)
    : _output(heater.distributor), _switcher(Switcher), _heater(heater)
{
}

Simulation::~Simulation()
{
}

void Simulation::SwitchOption()
{
    int _switch_ = _switcher;
    std::cout << "\n\nSwitch off using the negative value";
    std::cout << "\nExit with: 99 \n\n";
    int result = 0;
    while (1)
    {
        if (_switch_ < 0) // case negative - off switching
        {
            result = utils::ConvertOutput(_switch_) * -1;
            _output.TurnOff(static_cast<u_int>(result));
        }
        else
        {
            result = utils::ConvertOutput(_switch_);
            _output.TurnOn(static_cast<u_int>(result));
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Switch another on: ";
        std::cin >> _switch_;
        if (_switch_ == 99)
        {
            break;
        }
        else if (_switch_ == 100)
        {
            _switch_ = 0;
            _output.SwitchAllOn();
        }
        else if (_switch_ == 200)
        {
            _switch_ = 0;
            _output.SwitchAllOff();
        }
    }
}

void Simulation::run()
{
    // auto switches = _output.GetSwitches();
    // _output.SwitchAllOn();
    // std::this_thread::sleep_for(std::chrono::seconds(2));
    // _output.SwitchAllOff();

    int cout = 10;
    unsigned int numSwitch = 0;
    while (cout > 0)
    {
        cout--;
        _output.TurnOn(0);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        _output.TurnOff(0);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    EXIT_SUCCESS;
    // _output.SwitchAllOn();
    // std::this_thread::sleep_for(std::chrono::seconds(10));
    // _output.SwitchAllOff();

    // std::cout << "small checkout menu\n";
    // std::cout << "Enter a number 0 - X to switch on for 2 sec (break with 99)- ";
    // while (true)
    // {
    //     std::cout << "number: ";
    //     std::cin >> numSwitch;
    //     if (numSwitch == 99)
    //     {
    //         break;
    //     }
    //     else if (numSwitch < 10)
    //     {
    //         _output.TurnOn(switches[numSwitch]);
    //         std::this_thread::sleep_for(std::chrono::seconds(2));
    //         _output.TurnOff(switches[numSwitch]);
    //     }
    // }
}

} // namespace sfh