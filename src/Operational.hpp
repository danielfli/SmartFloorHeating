#pragma once
#include "../include/smartfloorheating/HeatingConstruction.hpp"
#include "Output.hpp"
#include "Thermostat.hpp"
#include "TwoLevelController.hpp"
#include <chrono>
#include <thread>
#include <vector>

namespace sfh
{
class Operational
{
  private:
    Thermostat _input;
    Output _output;
    HeatingConstruction _heater;
    std::vector<TwoLevelController> _veccontrol;

  public:
    Operational(HeatingConstruction heater, Thermostat &input, Output &output);
    ~Operational();

    bool Run();
};

Operational::Operational(HeatingConstruction heater, Thermostat &input, Output &output)
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
    std::cout << "\n\n_____START APP_____\n";

    //ToDo: Ablauf
    //! 1. Input 0 - x einlesen
    //! 2. Verarbeiten 0 - x verarbeiten
    //! 3. Output  (3.1: State , 3.2: schalten )  0 - x ausgeben
    auto inputDevice = _input.GetInputDevices();
    auto output = _output.GetSwitches();

    for (size_t i = 0; i < inputDevice.size(); i++)
    {
        std::cout << "\ncycle # " << i << " " << inputDevice[i].name << " switch GPIO: " << output[i].name
                  << " id: " << output[i].id << "\n";
    }

    Heater_Data heater_currentState{};
    Heater_Data heater_SetState{};

    //TEST GET - SET STATE VALUE
    for (size_t i = 0; i < inputDevice.size(); i++)
    {
        // GET
        heater_currentState = _input.GetStateData(output[i].entity_id, false);
        std::cout << "\n\nCURRENT STATE: heater id: " << heater_currentState.entity_id
                  << " heater state: " << heater_currentState.state << "\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        //SET all to TRUE
        heater_currentState.SetStateTrue();
        heater_SetState = _input.SetHeaterState(heater_currentState, false);
        std::cout << "RETURNSTATE:: heater id: " << heater_SetState.entity_id
                  << " heater state: " << heater_SetState.state << "\n";
    }

    // int count1 = 0;
    // while (true)
    // {
    //     count1++;
    //     std::cout << "Runde\n";
    //     //     // _input.GetTherostatData()
    //     std::this_thread::sleep_for(std::chrono::seconds(5));
    //     if (count1 == 2)
    //     {
    //         break;
    //     }
    // }
    return true;
}

} // namespace sfh
