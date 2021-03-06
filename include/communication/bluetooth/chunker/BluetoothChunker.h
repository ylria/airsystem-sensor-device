#pragma once

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <iterator>
#include <vector>
#include "NimBLEDevice.h"
#include "communication/bluetooth/chunker/BLEChunkerCallback.h"
#include "communication/bluetooth/chunker/BluetoothChunkerCallback.h"
#include "maintenance/Logger.h"

#define BT_CHUNKER_TIMEOUT 10     // timeout in sec
#define BT_MTU 20                 // in bytes
#define BT_CHUNKER_HEADER_SIZE 1  // in bytes

class BLEChunkerCallback;
class BluetoothChunkerCallback;

class BluetoothChunker {
 public:
  BluetoothChunker(BLEService* pService, const char* cuuid, const uint32_t access);
  ~BluetoothChunker();

  bool startReceiving(std::string& firstChunk);
  void endReceiving();
  bool isActiveReceiving();

  std::string startSending();
  void endSending();
  bool isActiveSending();

  void setCallback(BluetoothChunkerCallback* callback);

  bool setValue(std::string value);
  std::string getValue();

  std::string getChunk();
  void addChunk(std::string value);

 private:
  BLECharacteristic* characteristic;
  std::string value;
  BluetoothChunkerCallback* callback;
  BLEChunkerCallback* BLECallback;

  bool activeReceiving = false;
  unsigned long toReceiveChunkCount;
  unsigned long receiveChunkCount;
  unsigned long receiveTimestamp = 0;
  unsigned long maxBufferSize = 10;
  std::vector<std::string> buffer;

  bool activeSending = false;
  unsigned long toSendChunkCount;
  unsigned long sentChunkCount;
  unsigned long sentTimestamp = 0;

  bool isReceiverTimeout();
  bool isSenderTimeout();
  void clearReceivingTransaction();
  void clearSendingTransaction();
};
