#include "Output.hpp"
#include <array>
#include <bcm2835.h>
#include <chrono>
#include <iostream>
#include <string>
#include <string_view>
#include <thread>

namespace sfh
{
constexpr int MAX_GPIO = 10;
constexpr std::array<uint8_t, 12> Pin = {
    17, // 11
    18, // 12
    27, // 13
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

Output::Output(std::vector<DeviceHeaterID> &vecdeviceoutput, const size_t num, bool verbose) : InitSuccess(false)
{
    InitSuccess = bcm2835_init();
    if (!InitSuccess)
    {
        std::cout << "Failed to Init Output...\n";
        EXIT_FAILURE;
    }

    size_t count = 0;

    if (num > MAX_GPIO)
    {
        count = MAX_GPIO;
        std::cout << "WARNING - using Max GPIO: " << MAX_GPIO << "\n";
    }
    else
    {
        count = num;
    }

    std::cout << "\n\n_____Set Output_____\n";
    // DeviceHeaterID device{};
    _output = vecdeviceoutput;

    for (size_t i = 0; i < count; i++)
    {
        if (verbose)
        {
            std::cout << "distributor " << i << " on Pin: " << Pin[i] << " with GPIO name: " << PinName[i] << "\n";
        }

        _output[i].id = Pin[i];
        // set pins to an _output
        bcm2835_gpio_fsel(static_cast<uint8_t>(Pin[i]), BCM2835_GPIO_FSEL_OUTP);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    if (num != count)
    {
        //ToDO: one temp sensor for more than one distributor
        std::cout << "\n_____WARNING! Device Information are not the same_____\n";
        std::cout << "floorheatingconfig.json - distributor: " << num << "\n";
        std::cout << "WARNING: more configuration are needed!\n";
    }
}

Output::~Output()
{
    std::cout << "__SMART FLOOR HEATING__ ALL OFF\n";
    SwitchAllOff();
    bcm2835_close();
}

/**
 * @brief Elegoo 8 Kanal DC 5V Relaismodul
 * https://amzn.eu/d/4pwvRF8
 * @param id Pin numnber
 */

void Output::SwitchAllOn()
{

    for (size_t i = 0; i < _output.size(); i++)
    {
        std::cout << i << " pin on\n";
        // Turn it on
        bcm2835_gpio_write(static_cast<uint8_t>(_output[i].id), HIGH);
    }
}

void Output::SwitchAllOff()
{
    for (size_t i = 0; i < _output.size(); i++)
    {
        std::cout << i << " pin off\n";
        // Turn it off
        bcm2835_gpio_write(static_cast<uint8_t>(_output[i].id), LOW);
    }
}

std::vector<DeviceHeaterID> Output::GetSwitches() const
{
    return _output;
}

void Output::TurnOn(const size_t id)
{
    if (id == 0 || id < _output.size())
    {
        for (size_t i = 0; i < _output.size(); i++)
        {
            if (_output[i].id == id)
            {
                std::cout << "pin " << id << " - name: " << PinName[id] << " --> on\n";

                bcm2835_gpio_write(static_cast<uint8_t>(id), HIGH);
            }
        }
    }
    else
    {
        std::cout << id << " unknown -> operation not permitted \n";
    }
}

void Output::TurnOff(const int unsigned id)
{
    if (id == 0 || id < _output.size())
    {
        for (size_t i = 0; i < _output.size(); i++)
        {
            if (_output[i].id == id)
            {
                std::cout << "pin " << id << " - name: " << PinName[id] << " --> off\n";

                bcm2835_gpio_write(static_cast<uint8_t>(id), LOW);
            }
        }
    }
    else
    {
        std::cout << id << " unknown -> operation not permitted \n";
    }
}

} // namespace sfh