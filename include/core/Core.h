#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include "api/Api.h"
#include "communication/bluetooth/Bluetooth.h"
#include "communication/bluetooth/BluetoothHandler.h"
#include "communication/bluetooth/BluetoothRefreshHandler.h"
#include "communication/common/Internet.h"
#include "communication/gsm/GSM.h"
#include "config/Config.h"
#include "config/HardwareConfig.h"
#include "config/MeasurementType.h"
#include "core/AirAndGpsSensorStrategy.h"
#include "device/AirSensor.h"
#include "device/DeviceContainer.h"
#include "device/GpsSensor.h"
#include "device/Heater.h"
#include "device/PowerSensor.h"
#include "device/Storage.h"
#include "device/WeatherSensor.h"
#include "maintenance/Guardian.h"
#include "maintenance/Logger.h"
#include "maintenance/Statistics.h"
#include "maintenance/Guardian.h"
#include "device/DeviceContainer.h"
#include "config/HardwareConfig.h"
#include "util/StorableBuffer.h"

class Core {
public:
  Core() : storableBuffer("m") {};
  ~Core() {};
  void setUp();
  void main();
  bool isError();
  void reset();
  bool sendMeasurements();

 private:
  WeatherSensor *weatherSensor = NULL;
  PowerSensor *powerSensor = NULL;
  Heater *heater = NULL;
  Storage *storage = NULL;
  GSM *gsm = NULL;
  AirAndGpsSensorStrategy *airAndGpsSensorStrategy = NULL;

  MeasurementType measurementType;
  bool error = true;
  unsigned long lastErrorMillis = 0;
  unsigned long lastPublishMillis = 0;
  unsigned long lastGpsUpdateMillis = 0;
  bool isWorking = true;
  StorableBuffer storableBuffer;
  void tryPublishMeasurement();
};

extern Core core;
