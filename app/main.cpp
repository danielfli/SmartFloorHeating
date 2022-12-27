
#include "../include/smartfloorheating/SmartFloorHeater.hpp"

#include <exception>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    std::cout << "SMART FLOOR HEATING starting!\n";
    sfh::SmartFloorHeater mysfh;

    try
    {
        mysfh.DoSomeInput();
        // mysfh.DoSomeControl();
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
