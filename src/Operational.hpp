#pragma once
#include "Input.hpp"
#include "Output.hpp"
#include "TwoLevelController.hpp"
#include <vector>

namespace sfh
{
class Operational
{
  private:
    Input _input;
    Output _output;
    std::vector<TwoLevelController> _veccontrol;

  public:
    Operational(Input input, Output output);
    ~Operational();
};

Operational::Operational(Input input, Output output) : _input(input), _output(output), _veccontrol()
{
}

Operational::~Operational()
{
}

} // namespace sfh
