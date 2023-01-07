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
    off,
    heating,
    idle
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

struct Heater_Data
{
    bool state;
    std::string entity_id;

    void SetStateTrue()
    {
        state = true;
    }
};

struct HAApi
{
    std::string token;
    std::string ip;
    std::string port;
};

class Thermostat
{
  private:
    std::vector<DeviceThermostat> _vecdeviceInfo;
    std::vector<DeviceHeaterID> _vecdeviceoutput;
    HAApi _api;

  public:
    Thermostat(HeatingConstruction heater, bool verbose);
    ~Thermostat() = default;

    const std::vector<DeviceThermostat> &GetInputDevices();
    const std::vector<DeviceHeaterID> &GetOutputDevices();

    Thermostat_Data GetTherostatData(std::string deviceId, bool verbose, bool dryrun = false);
    Heater_Data GetStateData(std::string heaterId, bool verbose, bool dryrun = false);
    Heater_Data SetHeaterState(Heater_Data heater, bool verbose, bool dryrun = false);
};

} // namespace sfh