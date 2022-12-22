#pragma once
#include <string>
#include <vector>

namespace sfh
{

struct TuyaAPIEnv
{
    const std::string url = "https://openapi.tuyaeu.com";
    std::string client_id;
    std::string secret;
    std::string device_id;
    std::string easy_sign;
    std::string easy_access_token;
    std::string easy_refresh_token;
    int expire_time;
    // std::string refresh_token;
};

struct TokenResult
{
    std::string access_token;
    int expire_time;
    std::string refresh_token;
    std::string uid;
    bool success;
    u_long time_response;
    std::string tid;
};

class Input
{
  private:
    TuyaAPIEnv _apiEnv;
    TokenResult _responseToken;

  public:
    Input();
    ~Input();
    
    void DebugHash();
    
    void DebugResponse();

    bool DoConfiguration();

    bool GetAccessToken(bool verbose, bool dryrun = false);
    bool GetDeviceInfos();
};

} // namespace sfh