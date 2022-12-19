#include "Output.hpp"
#include <iostream>

// #include <bcm2835.h>

namespace sfh
{
Output::Output(/* args */)
{
}

Output::~Output()
{
}

void Output::SwitchOn()
{
    std::cout << "switch on\n";
}
} // namespace sfh