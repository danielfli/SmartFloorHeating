#pragma once
#include "../include/smartfloorheating/HeatingConstruction.hpp"
#include "Output.hpp"
#include "Thermostate.hpp"
#include "TwoLevelController.hpp"
#include <vector>
#include <thread>
#include <chrono>

namespace sfh
{
class Operational
{
  private:
    Thermostate _input;
    Output _output;
    HeatingConstruction _heater;
    std::vector<TwoLevelController> _veccontrol;

  public:
    Operational(HeatingConstruction heater, Thermostate input, Output output);
    ~Operational();

    bool Run();
};

Operational::Operational(HeatingConstruction heater, Thermostate input, Output output)
    : _input(input), _output(output), _heater(heater)
{
    for (size_t i = 0; i < heater.thermostat; i++)
    {
        // _veccontrol[1].
    }
}

Operational::~Operational()
{
}

bool Operational::Run()
{
    std::cout << "_____START APP_____\n";

    //ToDo: Ablauf
    //! 1. Input 0 - x einlesen
    //! 2. Verarbeiten 0 - x verarbeiten
    //! 3. Output  (3.1: State , 3.2: schalten )  0 - x ausgeben
    auto inputDevice = _input.GetInputDevices();
    auto output = _output.GetSwitches();

    for (size_t i = 0; i < inputDevice.size(); i++)
    {
        std::cout << "Cycle # " << i << " " << inputDevice[i].name << " switch: " << output[i].name << " id: " << output[i].id <<  "\n";
    }

    // while (true)
    // {
    //     // _input.GetTherostatData()
    std::this_thread::sleep_for(std::chrono::seconds(5));
    // }
    return true;
}

} // namespace sfh
