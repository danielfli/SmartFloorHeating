#include "Simulation.hpp"
#include <chrono>
#include <iostream>
#include <thread>

namespace sfh
{
Simulation::Simulation(Thermostat &thermostat, const Output &output) : _thermostat(thermostat), _output(output)
{
}

Simulation::~Simulation()
{
}

void Simulation::RunMaunal()
{
    std::vector<sfh::DeviceHeaterID> switches = _output.GetSwitches();
    std::vector<sfh::DeviceThermostat> thermostats = _thermostat.GetInputDevices();
    auto distributor = _thermostat.GetOutputDevices();

    int on = 0;
    std::cout << "\nexit with 33 -";
    std::cout << " all on with 100 -";
    std::cout << " all off with -100: ";
    std::cout << "\nConfigure SWITCHES: " << switches.size() << "\n";
    Thermostat_Data thermostatData{};
    Heater_Data distributorStatePre{};
    Heater_Data distributorStatePost{};

    while (1)
    {

        std::cout << "Switch on/off: ";
        std::cin >> on;
        switch (on)
        {
        case 1:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[0].entity_id, false);
            _output.TurnOn(switches[0].id);
            distributorStatePost = _thermostat.SetHeaterState({true, distributor[0].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[0].id, false);
            break;

        case 2:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[1].entity_id, false);
            _output.TurnOn(switches[1].id);
            distributorStatePost = _thermostat.SetHeaterState({true, distributor[1].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[1].id, false);
            break;

        case 3:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[2].entity_id, false);
            _output.TurnOn(switches[2].id);
            distributorStatePost = _thermostat.SetHeaterState({true, distributor[2].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[2].id, false);
            break;

        case 4:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[3].entity_id, false);
            _output.TurnOn(switches[3].id);
            distributorStatePost = _thermostat.SetHeaterState({true, distributor[3].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[3].id, false);
            break;

        case 5:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[4].entity_id, false);
            _output.TurnOn(switches[4].id);
            distributorStatePost = _thermostat.SetHeaterState({true, distributor[4].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[4].id, false);
            break;

        case 6:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[5].entity_id, false);
            _output.TurnOn(switches[5].id);
            distributorStatePost = _thermostat.SetHeaterState({true, distributor[5].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[5].id, false);
            break;

        case 7:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[6].entity_id, false);
            _output.TurnOn(switches[6].id);
            distributorStatePost = _thermostat.SetHeaterState({true, distributor[6].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[6].id, false);
            break;

        case 8:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[7].entity_id, false);
            _output.TurnOn(switches[7].id);
            distributorStatePost = _thermostat.SetHeaterState({true, distributor[7].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[7].id, false);
            break;

        case 9:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[8].entity_id, false);
            _output.TurnOn(switches[8].id);
            distributorStatePost = _thermostat.SetHeaterState({true, distributor[8].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[8].id, false);
            break;

        case 10:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[9].entity_id, false);
            _output.TurnOn(switches[9].id);
            distributorStatePost = _thermostat.SetHeaterState({true, distributor[9].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[9].id, false);
            break;

        case -1:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[0].entity_id, false);
            _output.TurnOff(switches[0].id);
            distributorStatePost = _thermostat.SetHeaterState({false, distributor[0].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[0].id, false);
            break;

        case -2:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[1].entity_id, false);
            _output.TurnOff(switches[1].id);
            distributorStatePost = _thermostat.SetHeaterState({false, distributor[1].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[1].id, false);
            break;

        case -3:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[2].entity_id, false);
            _output.TurnOff(switches[2].id);
            distributorStatePost = _thermostat.SetHeaterState({false, distributor[2].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[2].id, false);
            break;

        case -4:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[3].entity_id, false);
            _output.TurnOff(switches[3].id);
            distributorStatePost = _thermostat.SetHeaterState({false, distributor[3].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[3].id, false);
            break;

        case -5:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[4].entity_id, false);
            _output.TurnOff(switches[4].id);
            distributorStatePost = _thermostat.SetHeaterState({false, distributor[4].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[4].id, false);
            break;

        case -6:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[5].entity_id, false);
            _output.TurnOff(switches[5].id);
            distributorStatePost = _thermostat.SetHeaterState({false, distributor[5].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[5].id, false);
            break;

        case -7:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[6].entity_id, false);
            _output.TurnOff(switches[6].id);
            distributorStatePost = _thermostat.SetHeaterState({false, distributor[6].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[6].id, false);
            break;

        case -8:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[7].entity_id, false);
            _output.TurnOff(switches[7].id);
            distributorStatePost = _thermostat.SetHeaterState({false, distributor[7].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[7].id, false);
            break;

        case -9:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[8].entity_id, false);
            _output.TurnOff(switches[8].id);
            distributorStatePost = _thermostat.SetHeaterState({false, distributor[8].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[8].id, false);
            break;

        case -10:
            std::cout << "\n\n";
            distributorStatePre = _thermostat.GetStateData(distributor[9].entity_id, false);
            _output.TurnOff(switches[9].id);
            distributorStatePost = _thermostat.SetHeaterState({false, distributor[9].entity_id}, false);
            thermostatData = _thermostat.GetTherostatData(thermostats[9].id, false);
            break;

        case 100:
            _output.SwitchAllOn();
            break;
        case -100:
            _output.SwitchAllOff();
            break;
        default:
            break;
        }

        if (on == 33)
            break;

        std::cout << "Room: " << thermostatData.friendly_name << " - Current Temp: " << thermostatData.currentValueTemp
                  << " - Set Temp: " << thermostatData.setValueTemp << "\n";
        std::cout << std::boolalpha << "State pre: " << distributorStatePre.state
                  << " - state post: " << distributorStatePost.state << "\n\n";
    }
}

} // namespace sfh

// namespace utils
// {
// int ConvertOutput(int switcher)
// {
//     int result = 0;
//     // Convert to 1 - xx
//     if (switcher < 0)
//     {
//         result = switcher + 1;
//     }
//     else
//     {
//         result = switcher - 1;
//     }
//     return result;
// }
// } // namespace utils

// Simulation::Simulation(const HeatingConstruction heater, const int Switcher)
//     : _output(heater.distributor), _switcher(Switcher), _heater(heater)
// {
// }

// Simulation::~Simulation()
// {
// }

// void Simulation::SwitchOption()
// {
//     int _switch_ = _switcher;
//     std::cout << "\n\nSwitch off using the negative value";
//     std::cout << "\nExit with: 99 \n\n";
//     int result = 0;
//     while (1)
//     {
//         if (_switch_ < 0) // case negative - off switching
//         {
//             result = utils::ConvertOutput(_switch_) * -1;
//             _output.TurnOff(static_cast<u_int>(result));
//         }
//         else
//         {
//             result = utils::ConvertOutput(_switch_);
//             _output.TurnOn(static_cast<u_int>(result));
//         }

//         std::this_thread::sleep_for(std::chrono::seconds(1));
//         std::cout << "Switch another on: ";
//         std::cin >> _switch_;
//         if (_switch_ == 99)
//         {
//             break;
//         }
//         else if (_switch_ == 100)
//         {
//             _switch_ = 0;
//             _output.SwitchAllOn();
//         }
//         else if (_switch_ == 200)
//         {
//             _switch_ = 0;
//             _output.SwitchAllOff();
//         }
//     }
// }

// void Simulation::run()
// {
//     // auto switches = _output.GetSwitches();
//     // _output.SwitchAllOn();
//     // std::this_thread::sleep_for(std::chrono::seconds(2));
//     // _output.SwitchAllOff();

//     int cout = 10;
//     unsigned int numSwitch = 0;
//     while (cout > 0)
//     {
//         cout--;
//         _output.TurnOn(0);
//         std::this_thread::sleep_for(std::chrono::seconds(2));
//         _output.TurnOff(0);
//         std::this_thread::sleep_for(std::chrono::seconds(2));
//     }
//     EXIT_SUCCESS;
//     // _output.SwitchAllOn();
//     // std::this_thread::sleep_for(std::chrono::seconds(10));
//     // _output.SwitchAllOff();

//     // std::cout << "small checkout menu\n";
//     // std::cout << "Enter a number 0 - X to switch on for 2 sec (break with 99)- ";
//     // while (true)
//     // {
//     //     std::cout << "number: ";
//     //     std::cin >> numSwitch;
//     //     if (numSwitch == 99)
//     //     {
//     //         break;
//     //     }
//     //     else if (numSwitch < 10)
//     //     {
//     //         _output.TurnOn(switches[numSwitch]);
//     //         std::this_thread::sleep_for(std::chrono::seconds(2));
//     //         _output.TurnOff(switches[numSwitch]);
//     //     }
//     // }
// }

// } // namespace sfh