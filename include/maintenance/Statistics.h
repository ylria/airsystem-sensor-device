#pragma once

#include <ArduinoJson.h>
#include "config/Config.h"
#include "maintenance/Logger.h"
#include "time/Time.h"
#include "communication/common/Internet.h"
#include "device/DeviceContainer.h"

#define MAX_BUFFER_SIZE 30

enum StatisticPrivacyMode {
  publicMode,
  privateMode
};

enum StatisticType {
  oneStringValue,
  oneDoubleValue, 
  multiStringValue, 
  multiDoubleAggregatableValue, 
  multiDoubleValue
};

class StatisticEntity {
public:
StatisticEntity() {}
  StatisticEntity(StatisticPrivacyMode _privacyMode, StatisticType _type, const char* _id) 
  : privacyMode(_privacyMode), type(_type), id(_id) {};
  ~StatisticEntity() {};

  StatisticPrivacyMode privacyMode;
  StatisticType type;
  const char* id;

  const char* getPrivacyMode() {
    if(privacyMode == StatisticPrivacyMode::publicMode) {
      return "public";
    }
    else if(privacyMode == StatisticPrivacyMode::privateMode) {
      return "private";
    }
    else return "";
  }

  const char* getStatisticType() {
    if(type == StatisticType::oneStringValue) {
      return "one_string_value";
    }
    else if(type == StatisticType::oneDoubleValue) {
      return "one_double_value";
    }
    else if(type == StatisticType::multiStringValue) {
      return "multi_string_value";
    }
    else if(type == StatisticType::multiDoubleAggregatableValue) {
      return "multi_double_aggregatable_value";
    }
    else if(type == StatisticType::multiDoubleValue) {
      return "multi_double_value";
    }
    else return "";
  }

};

class StatisticsClass {
public:
  void reportBootUp();
  void reportConnectioniType();
  void reportHeaterState(bool value);
  void reportHeaterTemp(String& value);
  void reportHeartbeat();
  void reportConnectionState();
  void reportPower();
  void reportPm();
  void reportWeather();

  bool createStatistic(StatisticEntity& statistic);
  bool sendStatistic(const char* statisticId, const char* value);
private:
  String getUrl() const;
  const char** buffer;
  unsigned char bufferSize = 0;
  bool isEmpty();
  void push(const char* value);
  const char* pop();
};

extern StatisticsClass Statistics;
