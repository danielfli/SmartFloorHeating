#include "../include/smartfloorheating/Option.hpp"
#include "../include/smartfloorheating/SmartFloorHeater.hpp"
#include <exception>
#include <iostream>
#include <string>

using namespace std;
using namespace sfh;

int main(int argc, char **argv)
{
    std::cout << "_____SMART FLOOR HEATING starting...\n";

    SFHOption option;
    if (10 == option.Parse(argc, argv))
    { 
        //show help and exit
        return 0;
    }

    try
    {
        SmartFloorHeater::GetInstance().Execute(option);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (...)
    {
        std::cerr << "Error was catched - Errors! " << '\n';
        return 1;
    }

    return 0;
}
