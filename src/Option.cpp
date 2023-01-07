#include "../include/smartfloorheating/Option.hpp"

namespace sfh
{
// namespace utils
// {

// void on_age(int age)
// {
//     std::cout << "On age: " << age << '\n';
// }
// } // namespace utils

int SFHOption::Parse(int argc, char **argv)
{
    try
    {
        options_description generalOptions{"Options"};
        generalOptions.add_options()("help,h", "Help")
        ("verbose,v",value<bool>(&verbose)->default_value(false),"Show more output")
        ("state,s",value<int>(&runstate)->default_value(0),"0: operation (default) \n10: simualtion\n20: manual mode")
        ("percent,p",value<u_int>(&percent)->default_value(2),"(default: 2 %) hysteresis in percent: 0-100 '%' step 1 '%'");
        // ("switchOn,w",value<int>(&switchOn), "easy on/off switching");

        variables_map vm;
        store(parse_command_line(argc, argv, generalOptions), vm);
        notify(vm);

        if (vm.count("help"))
        {
           std::cout << generalOptions << '\n';
            return 10;
        
        // if (vm.count("switchOn"))
        //     std::cout << "Got switch on/off: " << vm["switchOn"].as<int>() << "\n";
        }
        else if (vm.count("state"))
        {
            switch (vm["state"].as<int>())
            {
            case 0:
                std::cout << "\nSTATE:  OPERATION \n";
                break;

            case 10:
                std::cout << "\nSTATE:  SIMULATION \n";
                break;

            case 20:
                std::cout << "\nSTATE:  MANUAL MODUE \n";
                break;

            default:
                std::cout << "\nSTATE:  WRONG STATE \n";
                EXIT_FAILURE;
                break;
            }
        }
    }
    catch (const error &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 0;
}

} // namespace sfh