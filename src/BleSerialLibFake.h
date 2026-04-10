#pragma once
#include "BleSerialDefines.h"
#ifdef BLE_SERIAL_BLE_LIB_FAKE
#include "BleSerialUuids.h"
#include "BleSerialService.h"
#include <string>

using BleSerialServerFake = int;

class BleSerialLib
{
public:
    BleSerialLib();

    bool begin(const char* deviceName);
    void begin();
    bool begin(const std::string& deviceName);
    bool begin(BleSerialServerFake* server);
    bool begin(const char* deviceName,
               BleSerialService& serialService);
    void begin(BleSerialService& serialService);
    bool begin(const std::string& deviceName,
               BleSerialService& serialService);
    bool begin(BleSerialServerFake* server,
               BleSerialService& serialService);

    void write(const uint8_t* data, size_t size);

private:
    void send(const uint8_t* data, size_t size);
};

extern BleSerialLib ArduinoBleSerial;
#endif