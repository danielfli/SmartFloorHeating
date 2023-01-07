#pragma once
#include <boost/program_options.hpp>
#include <iostream>

using namespace boost::program_options;

//states:
// 0. Operation
// 10. Simualtion (Test run)
// 20. Manual mode

namespace sfh
{
class SFHOption
{
  public:
    int Parse(int argc, char **argv);

    int switchOn = 99;
    bool verbose;
    int runstate;
    u_int percent;
};

} // namespace sfh