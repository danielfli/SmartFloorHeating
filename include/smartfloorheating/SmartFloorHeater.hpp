#pragma once
#include "Option.hpp"

namespace sfh
{

//sigleton pattern
class SmartFloorHeater
{
  public:
    SmartFloorHeater(SmartFloorHeater &other) = delete; // no cloneable
    void operator=(const SmartFloorHeater &) = delete;  // no assignable

    static SmartFloorHeater &GetInstance();

    void Execute(SFHOption &option);

  private:
    SmartFloorHeater();
    static SmartFloorHeater *_instance;

};
} // namespace sfh
