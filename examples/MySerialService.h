#pragma once
#include <ArduinoBleSerial.h>

class MySerialService : public BleSerialService
{
public:
  void handleData(const uint8_t* data, size_t size) override {
    Serial.write(data, size);
    Serial.println();
  }
  void checkSerialData() {
    if (Serial.available()) {
      String str = Serial.readString();
      sendData((const uint8_t*)str.c_str(), str.length());
    }
  }
};