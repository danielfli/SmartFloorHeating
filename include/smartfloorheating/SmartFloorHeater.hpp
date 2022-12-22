#pragma once

#include "Construction.hpp"

#include <map>
#include <string>

namespace sfh
{

class SmartFloorHeater
{
  private:
    // std::map<std::string,const unsigned int> _distributor;
    // std::map<std::string,const unsigned int> _tempsensor;

  public:
    SmartFloorHeater();
    ~SmartFloorHeater();

    void DoSomeInput();
    void DoSomeOutput();
};
} // namespace sfh
