#pragma once

#include "../include/smartfloorheating/HeatingConstruction.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace sfh
{

// ToDo: Read Config
// Set Data

enum class States
{
    heating,
    idle,
    off
};

struct Thermostat
{
    States state;
    std::string str_state;
    double setValueTemp;
    double currentValueTemp;
    double min_temp;
    double max_temp;
    std::string friendly_name;
};

struct HAApi
{
  std::string token;
  std::string ip;
  std::string port;
};

class InputHAClimate
{
  private:
    std::vector<DeviceID> _vecdeviceInfo;
    HAApi _api;

  public:
    InputHAClimate(HeatingConstruction heater, bool verbose);
    ~InputHAClimate() = default;

    std::vector<DeviceID> GetDevicesIDs();

    Thermostat GetTherostatData(std::string deviceId, bool verbose, bool dryrun = false);
    bool SetHeaterState();
};

} // namespace sfh