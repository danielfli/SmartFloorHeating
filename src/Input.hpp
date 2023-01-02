#pragma once
#include "../include/smartfloorheating/HeatingConstruction.hpp"
#include <string>
#include <vector>

namespace sfh
{

struct TuyaAPIEnv
{
    std::string client_id;
    std::string secret;
    std::string device_id;
    std::string easy_sign;
    std::string easy_access_token;
    std::string easy_refresh_token;
    int expire_time;
    // std::string refresh_token;
};

struct TokenResult
{
    std::string access_token;
    int expire_time;
    std::string refresh_token;
    std::string uid;
    bool success;
    size_t time_response;
    std::string tid;
};

struct DeviceValue
{
    double temperature;
    double humidity;
    std::string battery_state;
    std::string id;
};

class Input
{
  private:
    TuyaAPIEnv _apiEnv;
    TokenResult _responseToken;
    std::vector<DeviceThermostat> _vecdeviceInfo;
    HeatingConstruction _heater;

  public:
    Input(HeatingConstruction heater);
    ~Input() = default;

    void DebugHash();
    void DebugResponse();

    bool DoConfiguration(bool verbose = false);

    bool GetApiAccessToken(bool verbose, bool dryrun = false);
    DeviceValue GetApiDeviceInformation(std::string deviceId, bool verbose, bool dryrun = false);

    std::vector<DeviceThermostat> GetDevicesIDs();
    double GetTemp(std::string id, bool verbose);
};

} // namespace sfh