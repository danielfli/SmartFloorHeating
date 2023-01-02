#pragma once
#include "../include/smartfloorheating/HeatingConstruction.hpp"

namespace sfh
{
class Builder
{
  private:
    bool _verbose;
    HeatingConstruction _heater;
    bool SetupHeater();

  public:
    Builder(bool verbose);
    ~Builder();

    void EasySwitchOn(const int switcher);
    void RunOpteration();
    void RunSimualtion();
    void RunMaunal();
};
} // namespace sfh