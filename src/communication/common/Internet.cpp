#include "communication/common/Internet.h"

Internet::Type Internet::type = Internet::None;

int Internet::start() {
  Internet::type = (Type)Config::getInternetConnectionType();
  return Internet::type == Internet::WIFI ? WiFiConn::start() : GsmConn::start();
}

void Internet::stop() {
  if (Internet::type == Internet::None) {
    return;
  }
  Internet::type == Internet::WIFI ? WiFiConn::stop() : GsmConn::stop();
}

Http::Response Internet::httpGet(const String& url) {
  String authorization = String("Bearer ") + Config::getAccessToken();
  return Internet::httpGet(url, authorization);
}

Http::Response Internet::httpGet(const String& url, String& authorization) {
  return Internet::type == Internet::WIFI ? WiFiConn::httpGet(url, authorization)
                                          : GsmConn::httpGet(url, authorization);
}

Http::Response Internet::httpPost(const String& url, String& body) {
  String authorization = String("Bearer ") + Config::getAccessToken();
  return Internet::httpPost(url, body, authorization);
}

Http::Response Internet::httpPost(const String& url, String& body, String& authorization) {
  return Internet::type == Internet::WIFI ? WiFiConn::httpPost(url, body, authorization)
                                          : GsmConn::httpPost(url, body, authorization);
}

Http::Response Internet::httpPut(const String& url, String& body, String& authorization) {
  return Internet::type == Internet::WIFI ? WiFiConn::httpPut(url, body, authorization)
                                          : GsmConn::httpPut(url, body, authorization);
}

bool Internet::isConnected() {
  return Internet::type == Internet::WIFI ? WiFiConn::isConnected() : GsmConn::isConnected();
}

bool Internet::isOk() {
  return Internet::type == Internet::WIFI ? WiFiConn::isOk() : GsmConn::isOk();
}

int Internet::resetType(Type type) {
  stop();
  if (type == Internet::GSM) {
    return GsmConn::start();
  } else if (type == Internet::WIFI) {
    return WiFiConn::start();
  }
}
