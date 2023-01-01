#include "Input.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/bind/bind.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <chrono>
#include <curl/curl.h>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>

#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <set>
#include <sstream>
#include <string>
#include <vector>

auto constexpr path = "/usr/local/etc/smartfloorheating/connectiontempapi.json";
auto constexpr pathDeviceInfo = "/usr/local/etc/smartfloorheating/tuyaDeviceInfos.json";

namespace sfh
{

namespace pt = boost::property_tree;
using namespace boost::placeholders;

namespace UTILS
{

size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::string GetCurrentTimestampStr()
{
    std::chrono::milliseconds ms
        = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    return std::to_string(ms.count());
}

ssize_t GetCurrentTimestamp()
{
    std::chrono::milliseconds ms
        = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    return static_cast<ssize_t>(ms.count());
}

std::string ToHMAC256Msg(std::string client_id, std::string timestamp)
{
    const std::string HTTPMethod = "GET";
    const std::string Content_SHA256_emty
        = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"; // emty body -> e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
    // const std::string Headers_emty = "";
    const std::string Url = "/v1.0/token?grant_type=1";
    std::string msg
        = client_id + timestamp + HTTPMethod + "\n" + Content_SHA256_emty + "\n" /*+ Headers_emty */ + "\n" + Url;

    return msg;
}

std::string ToHMAC256MsgDevice(std::string client_id,
                               std::string accessToken,
                               std::string timestamp,
                               std::string deviceId)
{
    const std::string HTTPMethod = "GET";
    const std::string Content_SHA256_emty
        = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"; // emty body -> e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
    // const std::string Headers_emty = "";
    const std::string Url = "/v1.0/devices/";
    std::string msg = client_id + accessToken + timestamp + HTTPMethod + "\n" + Content_SHA256_emty
                      + "\n" /*+ Headers_emty */ + "\n" + Url + deviceId;

    return msg;
}

std::string ToHMAC256(std::string data, std::string key)
{
    std::stringstream ss;
    HMAC_CTX *ctx = HMAC_CTX_new();
    unsigned int len;
    unsigned char out[EVP_MAX_MD_SIZE];
    HMAC_Init(ctx, key.c_str(), key.length(), EVP_sha256());
    HMAC_Update(ctx, (unsigned char *)data.c_str(), data.length());
    HMAC_Final(ctx, out, &len);
    HMAC_CTX_free(ctx);
    for (unsigned int i = 0; i < len; i++)
    {
        ss << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(out[i]);
    }
    return ss.str();
}

std::string ConvertUpperCase(std::string lowercase)
{
    boost::to_upper(lowercase);
    return lowercase;
}

boost::property_tree::ptree GetResponse(std::string JsonInput)
{
    const std::string _path = "/tmp/_repsonseapituya.json";
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

TokenResult GetTokenData(boost::property_tree::ptree response, bool verbose)
{
    TokenResult result{};

    bool state = response.get<bool>("success", NULL);
    if (state)
    {
        result.access_token = response.get<std::string>("result.access_token", "xxx");
        result.expire_time = response.get<int>("result.expire_time", 0);
        result.refresh_token = response.get<std::string>("result.refresh_token", "xxx");
        result.uid = response.get<std::string>("result.uid", "xxx");
        result.success = true;
        result.time_response = response.get<size_t>("t", 0);
        result.tid = response.get<std::string>("tid", "xxx");

        if (verbose)
        {
            std::cout << "result.access_token: " << result.access_token << std::endl;
            std::cout << "result.expire_time: " << result.expire_time << std::endl;
            std::cout << "result.refresh_token: " << result.refresh_token << std::endl;
            std::cout << "result.uid: " << result.uid << std::endl;
            std::cout << "result.success: " << result.success << std::endl;
            std::cout << "result.time_response: " << result.time_response << std::endl;
            std::cout << "result.tid: " << result.tid << std::endl;
        }
    }
    else
    {
        std::cout << "Error: GetToken API Tuya.\n";
        std::cout << " code: " << response.get<int>("code", -1) << "\n";
        std::cout << " msg: " << response.get<std::string>("msg", "xx") << "\n";
    }

    return result;
}

DeviceValue GetDeviceInformation(boost::property_tree::ptree response, bool verbose)
{
    DeviceValue deviceInfos{};

    bool state = response.get<bool>("success", NULL);
    if (state)
    {
        try
        {
            for (auto &&i : response.get_child("result.status"))
            {
                if ("va_temperature" == i.second.get_child("code").data())
                    deviceInfos.temperature = i.second.get<double>("value", 0.0);

                if ("va_humidity" == i.second.get_child("code").data())
                    deviceInfos.humidity = i.second.get<double>("value", 0.0);

                if ("battery_state" == i.second.get_child("code").data())
                    deviceInfos.battery_state = i.second.get<std::string>("value", "xxx");
            }
        }
        catch (std::exception &e)
        {
            std::cerr << "Error: " << e.what() << "\n";
        }
        if (verbose)
        {
            std::cout << "va_temperature: " << deviceInfos.temperature << std::endl;
            std::cout << "va_humidity: " << deviceInfos.humidity << std::endl;
            std::cout << "battery_state: " << deviceInfos.battery_state << std::endl;
        }
    }
    else
    {
        std::cout << "______Error: GetToken API Tuya.______\n";
        std::cout << " code: " << response.get<int>("code", -1) << "\n";
        std::cout << " msg: " << response.get<std::string>("msg", "xx") << "\n";
    }

    return deviceInfos;
}

void APISetup(TuyaAPIEnv &apiEnv, bool verbose)
{
    try
    {
        pt::ptree apisetting;
        pt::read_json(path, apisetting);

        auto data = apisetting.get_child("TuyaApiValues");

        apiEnv.client_id = data.get<std::string>("client_id", "xxx");
        apiEnv.secret = data.get<std::string>("secret", "xxx");
        apiEnv.device_id = data.get<std::string>("device_id", "xxx");

        if (verbose)
        {
            std::cout << "\n_____Read Tuya Inforamtion_____\n";
            std::cout << "client_id: " << apiEnv.client_id << " \n";
            std::cout << "secret: " << apiEnv.secret << " \n";
            std::cout << "device_id: " << apiEnv.device_id << " \n";
        }

        if (apiEnv.client_id == "xxx" && apiEnv.secret == "xxx" && apiEnv.device_id == "xxx")
        {
            std::cerr << "Error: Could not read: " << path << "\n";
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void APIDeviceSetup(std::vector<DeviceID> &deviceInfo)
{
    try
    {
        DeviceID devices{};
        pt::ptree apisetting;
        pt::read_json(pathDeviceInfo, apisetting);

        auto data = apisetting.get_child("tempdevices");
        for (auto &&i : data)
        {
            devices.name = i.first;
            devices.id = i.second.data();
            // devices.temperature = 0.0;
            // devices.humidity = 0.0;
            // devices.battery_state = "";
            deviceInfo.push_back(devices);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

} // namespace UTILS

Input::Input(HeatingConstruction heater) : _apiEnv(), _responseToken(), _vecdeviceInfo{}, _heater(heater)
{
}

bool Input::GetApiAccessToken(bool verbose, bool dryrun)
{
    bool result = false;
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://openapi.tuyaeu.com/v1.0/token?grant_type=1");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, UTILS::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        struct curl_slist *headers = NULL;

        auto str_client = ("client_id: " + _apiEnv.client_id);
        auto tp = UTILS::GetCurrentTimestampStr();
        auto str_tp = ("t: " + tp);
        auto str_sign
            = ("sign: "
               + UTILS::ConvertUpperCase(UTILS::ToHMAC256(UTILS::ToHMAC256Msg(_apiEnv.client_id, tp), _apiEnv.secret)));

        if (verbose)
        {
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
            std::cout << "\n_____API CALL Get TOKEN_____ \n";
            std::cout << "str_client: " << str_client << "\n";
            std::cout << "str_sign: " << str_sign << "\n";
            std::cout << "timestamp: " << tp << "\n";
            std::cout << "str_tp: " << str_tp << "\n";

            if (dryrun)
                return true;
        }

        headers = curl_slist_append(headers, str_client.c_str());
        headers = curl_slist_append(headers, str_sign.c_str());
        headers = curl_slist_append(headers, str_tp.c_str());
        headers = curl_slist_append(headers, "sign_method: HMAC-SHA256");
        headers = curl_slist_append(headers, "nonce: ");
        headers = curl_slist_append(headers, "stringToSign: ");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            result = false;
        }
        else
        {
            result = true;
        }

        if (verbose)
            std::cout << "RAW - Output: " << readBuffer << std::endl;

        _responseToken = UTILS::GetTokenData(UTILS::GetResponse(readBuffer), verbose);
        curl_easy_cleanup(curl); /* always cleanup */
    }

    curl_global_cleanup();
    return result;
}

DeviceValue Input::GetApiDeviceInformation(std::string deviceId, bool verbose, bool dryrun)
{
    DeviceValue result{};
    result.id = deviceId;
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        std::string str_URL = ("https://openapi.tuyaeu.com/v1.0/devices/" + deviceId);
        curl_easy_setopt(curl, CURLOPT_URL, str_URL.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, UTILS::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

        struct curl_slist *headers = NULL;
        auto str_client = ("client_id: " + _apiEnv.client_id);
        auto str_access_token = ("access_token: " + _responseToken.access_token);
        auto tp = UTILS::GetCurrentTimestampStr();
        auto str_tp = ("t: " + tp);
        auto str_sign = ("sign: "
                         + UTILS::ConvertUpperCase(UTILS::ToHMAC256(
                             UTILS::ToHMAC256MsgDevice(_apiEnv.client_id, _responseToken.access_token, tp, deviceId),
                             _apiEnv.secret)));

        if (verbose)
        {
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
            std::cout << "\n_____API CALL Get Device Information_____\n";
            std::cout << "str_URL: " << str_URL << "\n";
            std::cout << "str_client: " << str_client << "\n";
            std::cout << "str_access_token: " << str_access_token << "\n";
            std::cout << "str_sign: " << str_sign << "\n";
            std::cout << "timestamp: " << tp << "\n";
            std::cout << "str_tp: " << str_tp << "\n";

            if (dryrun)
                return result;
        }

        headers = curl_slist_append(headers, str_client.c_str());
        headers = curl_slist_append(headers, str_access_token.c_str());
        headers = curl_slist_append(headers, str_sign.c_str());
        headers = curl_slist_append(headers, str_tp.c_str());
        headers = curl_slist_append(headers, "sign_method: HMAC-SHA256");
        headers = curl_slist_append(headers, "nonce: ");
        headers = curl_slist_append(headers, "stringToSign: ");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return result;
        }

        if (verbose)
            std::cout << "RAW - Output: " << readBuffer << std::endl;

        result = UTILS::GetDeviceInformation(UTILS::GetResponse(readBuffer), verbose);
        curl_easy_cleanup(curl); /* always cleanup */
    }

    curl_global_cleanup();
    return result;
}

bool Input::DoConfiguration(bool verbose)
{
    UTILS::APISetup(_apiEnv, verbose);
    UTILS::APIDeviceSetup(_vecdeviceInfo);

    std::cout << "\n_____Read Device Inforamtion_____\n";
    unsigned int countTempDevice = 0;
    for (auto &&i : _vecdeviceInfo)
    {
        if (verbose)
        {
            std::cout << i.name << " " << i.id << "\n";
        }
        countTempDevice++;
    }

    if (_vecdeviceInfo[0].id == "" && _vecdeviceInfo[0].name == "")
        return false;

    if (_heater.temperatureSensor != countTempDevice)
    {
        std::cout << "\n_____WARNING! Device Information are not the same_____\n";
        std::cout << "floorheatingconfig.json - Temperaturesensor: " << _heater.temperatureSensor << "\n";
        std::cout << "Tuya API - Temperaturesensor: " << countTempDevice << "\n";
    }

    return true;
}

std::vector<DeviceID> Input::GetDevicesIDs()
{
    return _vecdeviceInfo;
}

double Input::GetTemp(std::string id, bool verbose)
{

    //ToDO: Get Token after expires
    if (_responseToken.access_token == "")
    {
        std::cout << "\n\n______Get new Tuya Token______"
                  << "\n";
        if (!GetApiAccessToken(verbose))
        {
            std::cout << "\n\nERROR - get new token\n";
            std::cout << "Working with old Data....\n";
        }
    }

    std::cout << "\n\n_____Get Temp for " << id << "______\n";
    DeviceValue device_value = GetApiDeviceInformation(id, verbose);

    return device_value.temperature;

    // DeviceInfo olddeviceInfo = __deviceinfo;
    //ToDO: API Call check token time
    // Check old Timestamp or timestamp
    // auto oldtime = 1672334008743; //1672341194987
    // auto actualtime = UTILS::GetCurrentTimestamp();
    // auto timediff = (UTILS::GetCurrentTimestamp() - oldtime); // _responseToken.time_response);
    // auto td2 = (int)timediff - _responseToken.expire_time;
    // std::cout << "actualtime: " << actualtime << "\n";
    // std::cout << "oldtime   : " << oldtime << "\n";
    // std::cout << "timediff: " << timediff << "\n";
    // std::cout << "td2: " << td2 << "\n";
}

} // namespace sfh