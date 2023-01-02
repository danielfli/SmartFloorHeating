#include "Thermostate.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/bind/bind.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <curl/curl.h>
#include <iostream>
#include <string>

namespace sfh
{

namespace pt = boost::property_tree;
using namespace boost::placeholders;

namespace utils
{

size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

boost::property_tree::ptree GetResponse(std::string JsonInput)
{
    const std::string _path = "/tmp/_repsonsethermo.json";
    std::ofstream _respose;
    _respose.open(_path);
    _respose << JsonInput;
    _respose.close();

    pt::ptree root;
    try
    {
        pt::read_json(_path, root);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return root;
}

Thermostat_Data ConvertDataToThermostat(boost::property_tree::ptree response, bool verbose)
{
    Thermostat_Data result{};
    result.currentValueTemp = response.get<double>("attributes.current_temperature", 99.9);
    result.friendly_name = response.get<std::string>("attributes.friendly_name", "xxx");
    result.max_temp = response.get<double>("attributes.max_temp", 99.9);
    result.min_temp = response.get<double>("attributes.min_temp", 99.9);
    result.setValueTemp = response.get<double>("attributes.min_temp", 99.9);
    result.str_state = response.get<std::string>("attributes.hvac_action", "");

    if (result.str_state == "idle")
        result.state = States::idle;

    if (result.str_state == "heating")
        result.state = States::heating;

    if (result.str_state == "off")
        result.state = States::off;

    if (verbose)
    {
        std::cout << "result.currentValueTemp: " << result.currentValueTemp << std::endl;
        std::cout << "result.friendly_name: " << result.friendly_name << std::endl;
        std::cout << "result.max_temp: " << result.max_temp << std::endl;
        std::cout << "result.min_temp: " << result.min_temp << std::endl;
        std::cout << "result.setValueTemp: " << result.setValueTemp << std::endl;
        std::cout << "result.str_state: " << result.str_state << std::endl;
    }

    return result;
}

void Setup(std::vector<DeviceThermostat> &vecdeviceInfo,
           std::vector<DeviceHeaterID> &vecdeviceoutput,
           HAApi &api,
           bool verbose)
{
    std::string _path = "/usr/local/etc/smartfloorheating/connectionhomeassistant.json";
    try
    {
        DeviceThermostat deviceinputid{};
        DeviceHeaterID deviceoutputid{};
        pt::ptree setting;
        pt::read_json(_path, setting);

        for (auto &&i : setting.get_child("thermostat.entity_id"))
        {
            deviceinputid.name = i.first;
            deviceinputid.id = i.second.data();
            vecdeviceInfo.push_back(deviceinputid);
        }

        api.token = setting.get<std::string>("api.token", "");
        api.ip = setting.get<std::string>("api.ip", "");
        api.port = setting.get<std::string>("api.port", "");

        for (auto &&i : setting.get_child("heater.entity_id"))
        {
            deviceoutputid.name = i.first;
            deviceoutputid.entity_id = i.second.data();
            vecdeviceoutput.push_back(deviceoutputid);
        }

        if (verbose)
        {
            std::cout << "\n_____Read Home Assistant Information_____\n";
            for (auto &&i : vecdeviceInfo)
            {
                std::cout << i.name << " " << i.id << std::endl;
            }
            std::cout << "port: " << api.port << std::endl;
            std::cout << "ip: " << api.ip << std::endl;
            std::cout << "token: " << api.token << std::endl;
        }

        if (vecdeviceInfo.empty() || api.token.empty() || api.ip.empty() || api.port.empty() || vecdeviceoutput.empty())
        {
            throw std::runtime_error("ERROR: Read Home Assistant Information - missing input." + _path);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

} // namespace utils

Thermostate::Thermostate(HeatingConstruction heater, bool verbose)
{
    utils::Setup(_vecdeviceInfo, _vecdeviceoutput, _api, verbose);

    std::cout << "\n_____Read Device Information_____\n";
    unsigned int countTempDevice = 0;

    for (auto &&i : _vecdeviceInfo)
    {
        if (verbose)
        {
            std::cout << i.name << " " << i.id << "\n";
        }
        countTempDevice++;
    }

    for (auto &&i : _vecdeviceoutput)
    {
        if (verbose)
        {
            std::cout << i.name << " " << i.entity_id << "\n";
        }
    }

    if (_vecdeviceInfo[0].id == "" && _vecdeviceInfo[0].name == "")
        std::cout << "______ERROR: Cloud not read deviceInfos.\n";

    if (heater.thermostat != countTempDevice)
    {
        //ToDO: one temp sensor for more than one distributor
        std::cout << "\n_____WARNING! Device Information are not the same_____\n";
        std::cout << "floorheatingconfig.json - Temperaturesensor: " << heater.temperatureSensor << "\n";
        std::cout << "thermostat number: " << countTempDevice << "\n";
        std::cout << "WARNING: more configuration are needed!\n";
    }
}

Thermostat_Data Thermostate::GetTherostatData(std::string deviceId, bool verbose, bool dryrun)
{
    Thermostat_Data thermostat{};
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl)
    {
        std::string str_url = "http://" + _api.ip + ":" + _api.port + "/api/states/" + deviceId;
        curl_easy_setopt(curl, CURLOPT_URL, str_url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, utils::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        struct curl_slist *headers = NULL;
        auto str_author = ("Authorization: Bearer " + _api.token);

        if (verbose)
        {
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
            std::cout << "\n_____API CALL - get thermostat data \n";
            std::cout << "url: " << str_url << "\n";

            if (dryrun)
                return thermostat;
        }

        headers = curl_slist_append(headers, str_author.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for curl errors */
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return thermostat;
        }

        if (verbose)
            std::cout << "RAW - Output: " << readBuffer << std::endl;

        if (readBuffer.size() < 50)
        {
            return thermostat;
        }
        else
        {
            thermostat = utils::ConvertDataToThermostat(utils::GetResponse(readBuffer), verbose);
        }
        curl_easy_cleanup(curl); /* always cleanup */
    }

    curl_global_cleanup();
    return thermostat;
}

std::vector<DeviceThermostat> Thermostate::GetInputDevices()
{
    return _vecdeviceInfo;
}

std::vector<DeviceHeaterID> Thermostate::GetOutputDevices()
{
    return _vecdeviceoutput;
}

bool Thermostate::SetHeaterState()
{
    return false;
}

} // namespace sfh