#include "Output.hpp"
#include <iostream>

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