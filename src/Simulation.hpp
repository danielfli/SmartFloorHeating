#pragma once
#include "../include/smartfloorheating/HeatingConstruction.hpp"
#include "Output.hpp"
#include "Thermostat.hpp"

namespace sfh
{

class Simulation
{
  private:
    Thermostat _thermostat;
    const Output _output;

  public:
    Simulation(Thermostat &thermostat, const Output &output);

    ~Simulation();

    void RunMaunal();
};

} // namespace sfh