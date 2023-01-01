#pragma once
#include <string>

namespace sfh
{
struct HeatingConstruction
{
    unsigned int distributor;
    unsigned int temperatureSensor;
};

struct DeviceID
{
    std::string name;
    std::string id;
};

} // namespace sfh