
#include "../include/smartfloorheading/SmartFloorHeater.hpp"

#include <iostream>

int main() {
  std::cout << "Hello cross build!\n";
  sfh::SmartFloorHeater mysfh;

  mysfh.DoSome();
  return 0;
}
