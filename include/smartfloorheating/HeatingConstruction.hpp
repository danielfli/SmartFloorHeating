#pragma once
#include <string>


namespace sfh
{
struct HeatingConstruction
{
    unsigned int distributor;
    unsigned int temperatureSensor;
    unsigned int thermostat;
};

struct DeviceThermostat
{
    std::string name;
    std::string id;
};

struct DeviceHeaterID
{
    std::string name;
    std::string entity_id;
    size_t id;
};

} // namespace sfh