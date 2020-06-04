#include "communication/wifi/WiFiConn.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "config/Config.h"
#include "maintenance/Logger.h"

static HTTPClient http;
int WiFiConn::start()
{
    WiFi.begin(Config::instance().getWifiSsid().c_str(), Config::instance().getWifiPassword().c_str());
    Serial.println("Connecting to wifi...");
    Serial.println(Config::instance().getWifiSsid());
    Serial.println(Config::instance().getWifiPassword());

    int i = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        i++;
        if (i > 8)
        {
            Serial.println("");
            Serial.println("WiFi - error!");
            return -1;
        }
        delay(1000);
    }
    Serial.println("WiFi - connected!");
    return 0;
}

void WiFiConn::stop()
{
    WiFi.disconnect();
}

Http::Response WiFiConn::httpGet(String url)
{
}

Http::Response WiFiConn::httpPost(String url, String json)
{
    Logger::debug(url.c_str());
    Logger::debug(json.c_str());

    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    if (!Config::instance().getAccessToken().equals(""))
    {
        Logger::debug("Setting authorization");
        Logger::debug((String("Bearer ") + Config::instance().getAccessToken()).c_str());
        http.addHeader("Authorization", String("Bearer ") + Config::instance().getAccessToken());
    }

    Http::Response response;
    response.code = http.POST(json);
    response.payload = http.getString();

    http.end();
    return response;
}

Http::Response WiFiConn::httpPut(String url, String json)
{
}

void WiFiConn::setHeader(String key, String value)
{
}