#pragma once
#include "BleSerialDefines.h"
#ifdef BLE_SERIAL_BLE_LIB_ARDUINO_BLE
#include "BleSerialUuids.h"
#include "BleSerialService.h"
#include "BleSerialSizes.h"

class BleSerialLib
{
public:
    BleSerialLib();

    bool begin(const char* deviceName);
    void begin();
    bool begin(const char* deviceName,
               BleSerialService& serialService);
    void begin(BleSerialService& serialService);

    void write(const uint8_t* data, size_t size);

private:
    void onWrite(const BLECharacteristic& characteristic);
    void send(const uint8_t* data, size_t size);
    static void onWrite(BLEDevice central, BLECharacteristic characteristic);

    BleSerialService* _serialService;
};

extern BleSerialLib ArduinoBleSerial;
#endif