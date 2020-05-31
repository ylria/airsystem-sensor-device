#pragma once

#include <Arduino.h>
#include "communication/common/Http.h"

class GsmConn
{

public:
    static int start();
    static void stop();
    static Http::Response httpGet(String url);
    static Http::Response httpPost(String url, String json);
    static Http::Response httpPut(String url, String json);
};