#pragma once
#include "../include/smartfloorheating/HeatingConstruction.hpp"
#include <iostream>
#include <vector>

namespace sfh
{

class Output
{
  private:
    bool InitSuccess;
    std::vector<DeviceHeaterID> _output;

  public:
    Output(std::vector<DeviceHeaterID>& vecdeviceoutput, const size_t num, bool verbose = false);
    ~Output();

    operator bool()
    {
        return InitSuccess;
    }

    void SwitchAllOn();

    void SwitchAllOff();

    void TurnOn(const int unsigned id);
    void TurnOff(const int unsigned id);

    std::vector<DeviceHeaterID> GetSwitches() const;
};

} // namespace sfh