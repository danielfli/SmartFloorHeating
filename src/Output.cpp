#include "Output.hpp"
#include <array>
#include <iostream>
#include <string>
#include <string_view>

// #include <bcm2835.h>

#include <bcm2835.h>

namespace sfh
{
constexpr int MAX_GPIO = 10;
constexpr std::array<uint8_t, 12> Pin = {
    17, // 11
    18, // 12
    21, // 13
    22, // 15
    23, // 16
    24, // 18
    10, // 19
    9,  // 21
    25, // 22
    11, // 23
    8,  // 24
    7,  // 26
};
//ToDo: Rename the name
constexpr std::array<std::string_view, 12> PinName{"RPI_GPIO_P1_11",
                                                   "RPI_GPIO_P1_12",
                                                   "RPI_GPIO_P1_13",
                                                   "RPI_GPIO_P1_15",
                                                   "RPI_GPIO_P1_16",
                                                   "RPI_GPIO_P1_18",
                                                   "RPI_GPIO_P1_19",
                                                   "RPI_GPIO_P1_21",
                                                   "RPI_GPIO_P1_22",
                                                   "RPI_GPIO_P1_23",
                                                   "RPI_GPIO_P1_24",
                                                   "RPI_GPIO_P1_26"};

Output::Output(const unsigned int num) : InitSuccess(false)
{
    InitSuccess = bcm2835_init();
    if (!InitSuccess)
    {
        std::cout << "Failed to Init Output...\n";
        EXIT_FAILURE;
    }

    unsigned int count = 0;

    if (num > MAX_GPIO)
    {
        count = MAX_GPIO;
    }
    else
    {
        count = num;
    }

    for (unsigned int i = 0; i < count; i++)
    {
        std::cout << i << " distributor Pin: " << Pin[i] << " GPIO " << PinName[i] << "\n";

        output.push_back(Pin[i]);

        // set pins to an output
        bcm2835_gpio_fsel(static_cast<uint8_t>(Pin[i]), BCM2835_GPIO_FSEL_OUTP);
    }
}

Output::~Output()
{
    bcm2835_close();
}

/**
 * @brief Elegoo 8 Kanal DC 5V Relaismodul
 * https://amzn.eu/d/4pwvRF8
 * @param id Pin numnber
 */

void Output::SwitchAllOn()
{
    for (auto &&i : output)
    {
        std::cout << i << " pin on\n";
        // Turn it on
        bcm2835_gpio_write(static_cast<uint8_t>(i), HIGH);
    }
}

void Output::SwitchAllOff()
{
    for (auto &&i : output)
    {
        std::cout << i << " pin off\n";
        //Turn it on
        bcm2835_gpio_write(static_cast<uint8_t>(i), LOW);
    }
}

std::vector<unsigned int> Output::GetSwitches() const
{
    return output;
}

void Output::TurnOn(const unsigned int id)
{
    std::cout << id << " pin on\n";

    //
    bcm2835_gpio_write(static_cast<uint8_t>(id), HIGH);
}

void Output::TurnOff(const int unsigned id)
{
    std::cout << id << " pin off\n";

    bcm2835_gpio_write(static_cast<uint8_t>(id), LOW);
}

} // namespace sfh