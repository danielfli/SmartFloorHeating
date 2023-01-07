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
    Thermostat _thermostat;
    const Output _output;
    std::vector<TwoLevelController> _veccontrol;

  public:
    Operational(Thermostat &thermostat, const Output &output, const u_int percent );
    ~Operational();

    bool Run();
};

} // namespace sfh
