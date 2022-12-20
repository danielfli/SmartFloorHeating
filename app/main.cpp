
#include "../include/smartfloorheating/SmartFloorHeater.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <exception>
#include <iostream>
#include <set>
#include <string>
namespace pt = boost::property_tree;

auto path = "/usr/local/etc/smartfloorheating/connectiontempapi.json";
// int main()
// {
//     std::cout << "Hello cross build!\n";
//     // sfh::SmartFloorHeater mysfh;

//     // mysfh.DoSome();
//     return 0;
// }

int main()
{
    try
    {
        pt::ptree apisetting;
        pt::read_json(path, apisetting);

        auto strid = apisetting.get<std::string>("id", "??");

        std::cout << "Some JSON Paser: " << strid << "\n";
        // for (auto &&i : apisetting)
        // {
        //     std::cout << "some: " << i.first << " more: " << i.second.data();
        // }

        std::cout << "Success\n";
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }
    return 0;
}
