#pragma once
#include "../include/smartfloorheating/HeatingConstruction.hpp"
#include "Output.hpp"

namespace sfh
{

class Simulation
{
  private:
    Output _output;
    const int _switcher;
    const HeatingConstruction _heater;

  public:
    Simulation(const HeatingConstruction heater, const int Switcher);
    ~Simulation();

    void run();

    void SwitchOption();
};

} // namespace sfh