#include "Builder.hpp"
#include "Input.hpp"
#include "Operational.hpp"
#include "Simulation.hpp"
#include "Thermostat.hpp"
#include <boost/bind/bind.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

auto constexpr pathConf = "/usr/local/etc/smartfloorheating/floorheatingconfig.json";

namespace sfh
{
namespace pt = boost::property_tree;
using namespace boost::placeholders;

Builder::Builder(bool verbose) : _verbose(verbose), _heater{}
{
}

Builder::~Builder()
{
}

bool Builder::SetupHeater()
{
    try
    {
        pt::ptree config;
        pt::read_json(pathConf, config);

        _heater.distributor = config.get<unsigned int>("distributor", 0);
        _heater.temperatureSensor = config.get<unsigned int>("temperaturesensor", 0);
        _heater.thermostat = config.get<unsigned int>("thermostat", 0);

        if (_verbose)
        {
            std::cout << "_____CONFIGURATION_____\n";
            std::cout << "Distributor: " << _heater.distributor << "\n";
            std::cout << "Temperature Sensor: " << _heater.temperatureSensor << "\n";
            std::cout << "Thermostat: " << _heater.thermostat << "\n";
        }

        if (_heater.distributor == 0 || _heater.temperatureSensor == 0)
        {
            std::cerr << "Wrong Configuration in: " << pathConf << "\n";
            return false;
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return true;
}

// void Builder::EasySwitchOn(const int switcher)
// {
//     if (SetupHeater())
//     {
//         // Simulation simu(_heater, switcher);
//         // simu.SwitchOption();
//         // simu.run();
//     }
//     else
//     {
//         EXIT_FAILURE;
//     }
// }

void Builder::RunOpteration(const u_int hysteresisPercent)
{
    if (!SetupHeater())
    {
        throw std::runtime_error("ERROR: Wrong configuration");
    }
    else
    {
        /************************Input****************************************/
        /************************Thermostat***********************************/
        Thermostat thermostats(_heater, _verbose);
        if (_verbose)
        {
            std::vector<DeviceThermostat> devices = thermostats.GetInputDevices();
            Thermostat_Data thermostat{};
            for (size_t i = 0; i < devices.size(); i++)
            {
                thermostat = thermostats.GetTherostatData(devices[i].id, _verbose);
                std::cout << i << " Device: " << thermostat.friendly_name
                          << " Temperatur: " << thermostat.currentValueTemp << "\n";
            }
        }

        /************************Output****************************************/
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        std::vector<DeviceHeaterID> outputdevices = thermostats.GetOutputDevices();
        Output output(outputdevices, _heater.distributor, _verbose);
        if (!output)
        {
            throw std::runtime_error("ERROR: output error ");
        }

        /************************Output***************************************/
        /************************State****************************************/
        if (_verbose)
        {
            Heater_Data heater_state{};
            for (size_t i = 0; i < outputdevices.size(); i++)
            {
                heater_state = thermostats.GetStateData(outputdevices[i].entity_id, _verbose);
                std::cout << i << " heater id: " << heater_state.entity_id << " heater state: " << heater_state.state
                          << "\n";
                // std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }

        /************************RUN*******************************************/
        std::this_thread::sleep_for(std::chrono::seconds(1));
        Operational op(thermostats, output, hysteresisPercent);
        op.Run();
    }
}

void Builder::RunMaunal()
{
    if (!SetupHeater())
    {
        throw std::runtime_error("ERROR: Wrong configuration");
    }
    else
    {
        /************************Input****************************************/
        /************************Thermostats**********************************/
        Thermostat thermostat(_heater, _verbose);
        if (_verbose)
        {
            std::vector<DeviceThermostat> devices = thermostat.GetInputDevices();
            Thermostat_Data thermostats{};
            Heater_Data heater_state{};
            for (size_t i = 0; i < devices.size(); i++)
            {
                thermostats = thermostat.GetTherostatData(devices[i].id, _verbose);
                std::cout << i << " Device: " << thermostats.friendly_name
                          << " Temperatur: " << thermostats.currentValueTemp << "\n";
                // std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }

        /************************Output****************************************/
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        std::vector<DeviceHeaterID> outputdevices = thermostat.GetOutputDevices();
        Output output(outputdevices, _heater.distributor, _verbose);
        if (!output)
        {
            throw std::runtime_error("ERROR: output error ");
        }

        /************************Simulation*************************************/
        Simulation simu(thermostat, output);
        simu.RunMaunal();
    }
}

void Builder::RunSimualtion()
{
    // void SmartFloorHeater::DoSomeOutput()
    // {
    //     unsigned int distr = 5;
    //     Output out{distr};
    //     auto switches = out.GetSwitches();
    //     // out.SwitchAllOn();
    //     int cout = 10;
    //     unsigned int numSwitch = 0;
    //     while (cout > 0)
    //     {
    //         cout--;
    //         out.TurnOn(switches[0]);
    //         std::this_thread::sleep_for(std::chrono::seconds(2));
    //         out.TurnOff(switches[0]);
    //         std::this_thread::sleep_for(std::chrono::seconds(2));
    //     }
    //     out.SwitchAllOn();
    //     std::this_thread::sleep_for(std::chrono::seconds(10));
    //     out.SwitchAllOff();

    //     std::cout << "small checkout menu\n";
    //     std::cout << "Enter a number 0 - X to switch on for 2 sec (break with 99)- ";
    //     while (true)
    //     {
    //         std::cout << "number: ";
    //         std::cin >> numSwitch;
    //         if (numSwitch == 99)
    //         {
    //             break;
    //         }
    //         else if (numSwitch < distr)
    //         {
    //             out.TurnOn(switches[numSwitch]);
    //             std::this_thread::sleep_for(std::chrono::seconds(2));
    //             out.TurnOff(switches[numSwitch]);
    //         }
    //     }
    // }
}
} // namespace sfh