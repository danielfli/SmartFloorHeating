#pragma once

#include "Construction.hpp"

#include <string>
#include <map>

namespace sfh
{

class SmartFloorHeater
{
  private:
    std::map<std::string,const unsigned int> _distributor;
    std::map<std::string,const unsigned int> _tempsensor;

  public:
    SmartFloorHeater(HeatingStructure heating);
    ~SmartFloorHeater();
};
} // namespace sfh
