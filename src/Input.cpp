#include "Input.hpp"
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/bind/bind.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <exception>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

#include <chrono>
#include <curl/curl.h>
#include <iomanip>
#include <iostream>
#include <openssl/evp.h>
#include <openssl/hmac.h>

auto constexpr path = "/usr/local/etc/smartfloorheating/connectiontempapi.json";

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

std::string ToHMAC256Msg(std::string client_id, std::string timestamp)
{
    const std::string _client_id = client_id;
    const std::string HTTPMethod = "GET";
    const std::string Content_SHA256_emty
        = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"; // emty body -> e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
    // const std::string Headers_emty = "";
    const std::string Url = "/v1.0/token?grant_type=1";
    std::string msg
        = _client_id + timestamp + HTTPMethod + "\n" + Content_SHA256_emty + "\n" /*+ Headers_emty */ + "\n" + Url;

    // std::cout << "\n \n msg: " << msg << "\n";
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
    // Output: {"result":{"access_token":"159827a6c1b5132657da993ca6a1ff5c","expire_time":4534,"refresh_token":"84cdde9be095b30186f8643e1182605d","uid":"bay1670956745243Nc6H"},"success":true,"t":1671740530441,"tid":"503ab894823611ed86f7ea3d2b411a8b"}
    std::cout << "RAW - Output: " << JsonInput << std::endl;
    pt::ptree root;
    pt::write_json(JsonInput, root);
    std::cout << "Test-Output: " << root.get<std::string>("success","xxx") << "\n";
    return root;
}

// HMAC Funktion von JS: CryptoJS.HmacSHA256
// std::string TuyaCryptoHmacSHA256(const char *msg, const char *secret)
// {
//     unsigned char *key = (unsigned char *)secret; //(unsigned char *)"This is your secret";
//     unsigned char *data = (unsigned char *)msg;   //(unsigned char *)"hoge";
//     unsigned char *expected = (unsigned char *)"0da44e4e0c39fb167b51400521afb13904111e440986cbde0a96619e9c527f07";
//     unsigned char *result;
//     int result_len = 32;
//     int i;
//     static char res_hexstring[64];
//     result = HMAC(EVP_sha256(), key, strlen((char *)key), data, strlen((char *)data), NULL, NULL);
//     for (i = 0; i < result_len; i++)
//     {
//         sprintf(&(res_hexstring[i * 2]), "%02x", result[i]);
//     }
//     if (strcmp((char *)res_hexstring, (char *)expected) == 0)
//     {
//         printf("Got %s\nTest ok, result length %d\n", res_hexstring, result_len);
//     }
//     printf("Not same - Got %s instead of %s\n", res_hexstring, expected);
//     return "";
// }

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
        result.time_response = response.get<u_long>("t", 0);
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

} // namespace UTILS

Input::Input(/* args */)
{
}

Input::~Input()
{
}

bool Input::DoConfiguration()
{
    try
    {
        pt::ptree apisetting;
        pt::read_json(path, apisetting);

        auto data = apisetting.get_child("TuyaApiValues");

        _apiEnv.client_id = data.get<std::string>("client_id", "xxx");
        _apiEnv.secret = data.get<std::string>("secret", "xxx");
        _apiEnv.device_id = data.get<std::string>("device_id", "xxx");

        std::cout << "client_id: " << _apiEnv.client_id << " \n";
        std::cout << "secret: " << _apiEnv.secret << " \n";
        std::cout << "device_id: " << _apiEnv.device_id << " \n";

        if (_apiEnv.client_id == "xxx" && _apiEnv.secret == "xxx" && _apiEnv.device_id == "xxx")
        {
            std::cerr << "Error: Could not read: " << path << "\n";
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
    return false;
}

void Input::DebugHash()
{
    auto time = std::to_string(1671737864061); //UTILS::GetCurrentTimestampStr();
    auto msg = UTILS::ToHMAC256Msg(_apiEnv.client_id, time);
    std::string hash = UTILS::ToHMAC256(msg, _apiEnv.secret);
    auto upphash = UTILS::ConvertUpperCase(hash);
    std::cout << "\nmsg: " << msg << "\n";
    std::cout << "\nHash: " << upphash << "\n";
}

void Input::DebugResponse()
{
        try
    {
        pt::ptree api_response;
        pt::read_json("/usr/local/etc/smartfloorheating/responseTokenError.json", api_response);

        UTILS::GetTokenData(api_response, true);
        // auto data = apisetting.get_child("TuyaApiValues");

    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

bool Input::GetAccessToken(bool verbose, bool dryrun)
{
    bool result = false;
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    // std::stringstream readBuffer;
    // char* readBuffer;
    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://openapi.tuyaeu.com/v1.0/token?grant_type=1");
        // curl_easy_setopt(curl, CURLOPT_URL, "https://example.com/");
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

        //ToDo: String nach ptree fehler!! sting obj in json to ptree ??? 
        UTILS::GetTokenData(UTILS::GetResponse(readBuffer), verbose);
        curl_easy_cleanup(curl); /* always cleanup */
    }

    curl_global_cleanup();

    return result;
}

bool Input::GetDeviceInfos()
{
    // CURL *curl;
    // CURLcode res;
    // curl = curl_easy_init();
    // if (curl)
    // {
    //     curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    //     curl_easy_setopt(curl, CURLOPT_URL, "https://openapi.tuyaeu.com/v1.0/devices/bf994fd645e428869fe6y8");
    //     curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    //     curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
    //     struct curl_slist *headers = NULL;
    //     headers = curl_slist_append(headers, "client_id: du773dh8ejkds3uu4n3q");
    //     headers = curl_slist_append(headers, "access_token: 0916b20a98a7042f9cf1b8ab9db784ee");
    //     headers = curl_slist_append(headers, "sign: E1BFAD89AC4AAD63E503E86F727BD7A22E98CB8FF6BC56A36968CCAA7E9C2266");
    //     headers = curl_slist_append(headers, "t: 1671565509836");
    //     headers = curl_slist_append(headers, "sign_method: HMAC-SHA256");
    //     headers = curl_slist_append(headers, "nonce: ");
    //     headers = curl_slist_append(headers, "stringToSign: ");
    //     curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    //     res = curl_easy_perform(curl);
    // }
    // curl_easy_cleanup(curl);
    return false;
}

} // namespace sfh