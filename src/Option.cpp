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

bool SFHOption::Parse(int argc, char **argv)
{
    try
    {
        options_description generalOptions{"Options"};
        generalOptions.add_options()("help,h", "Help")
        ("verbose,v",value<bool>(&verbose)->default_value(false),"Show more output")
        ("state,s", value<int>(&runstate)->default_value(0), "0: operation (default) \n10: simualtion\n20: manual mode")
        ("switchOn,w",value<int>(&switchOn),"easy on/off switching");
        // ("pi",value<float>(&pi)->default_value(3.14f),"Pi")
        // ("age", value<int>(&age)->notifier(utils::on_age), "Age")
        
        variables_map vm;
        store(parse_command_line(argc, argv, generalOptions), vm);
        notify(vm);

        if (vm.count("help"))
            std::cout << generalOptions << '\n';

        if (vm.count("switchOn"))
            std::cout << "Got switch on/off: " << vm["switchOn"].as<int>() << "\n";
        else
            if (vm.count("state"))
            {
                switch (vm["state"].as<int>())
                {
                case 0:
                    std::cout << "Smart Floor Header run in: OPERATION \n";
                    break;
                case 10:
                    std::cout << "Smart Floor Header run in: SIMULATION \n";
                    break;

                case 20:
                    std::cout << "Smart Floor Header run in: MANUAL MODUE \n";
                    break;

                default:
                    std::cout << "Smart Floor Header run in: WRONG STATE \n";
                    EXIT_FAILURE;
                    break;
                }
            }
    }
    catch (const error &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return true;
}

} // namespace sfh