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

struct Thermostat_Data
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

class Thermostate
{
  private:
    std::vector<DeviceThermostat> _vecdeviceInfo;
    std::vector<DeviceHeaterID> _vecdeviceoutput;
    HAApi _api;

  public:
    Thermostate(HeatingConstruction heater, bool verbose);
    ~Thermostate() = default;

    std::vector<DeviceThermostat> GetInputDevices();
    std::vector<DeviceHeaterID> GetOutputDevices();

    Thermostat_Data GetTherostatData(std::string deviceId, bool verbose, bool dryrun = false);
    bool SetHeaterState();
};

} // namespace sfh