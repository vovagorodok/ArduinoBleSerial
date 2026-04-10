#pragma once
#include "BleSerialDefines.h"
#ifdef BLE_SERIAL_BLE_LIB_ESP32
#include "BleSerialUuids.h"
#include "BleSerialService.h"

class BleSerialLib: public BLECharacteristicCallbacks
{
public:
    BleSerialLib();

    void begin(const std::string& deviceName);
    void begin(BLEServer* server);
    void begin(const std::string& deviceName,
               BleSerialService& serialService);
    void begin(BLEServer* server,
               BleSerialService& serialService);

    void write(const uint8_t* data, size_t size);

private:
    void onWrite(BLECharacteristic* characteristic) override;
    void send(const uint8_t* data, size_t size);

    BLECharacteristic* _txCharacteristic;
    BleSerialService* _serialService;
};

extern BleSerialLib ArduinoBleSerial;
#endif