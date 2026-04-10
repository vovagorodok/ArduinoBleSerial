#pragma once
#include "BleSerialDefines.h"
#ifdef BLE_SERIAL_BLE_LIB_NIM_BLE_ARDUINO
#include "BleSerialUuids.h"
#include "BleSerialService.h"

class BleSerialLib: public BLECharacteristicCallbacks
{
public:
    BleSerialLib();

    bool begin(const std::string& deviceName);
    bool begin(BLEServer* server);
    bool begin(const std::string& deviceName,
               BleSerialService& serialService);
    bool begin(BLEServer* server,
               BleSerialService& serialService);

    void write(const uint8_t* data, size_t size);

private:
#ifdef BLE_SERIAL_BLE_LIB_NIM_BLE_ARDUINO_V1
    void onWrite(BLECharacteristic* characteristic) override;
#else
    void onWrite(BLECharacteristic* characteristic, BLEConnInfo& connInfo) override;
#endif
    void send(const uint8_t* data, size_t size);

    BLECharacteristic* _txCharacteristic;
    BleSerialService* _serialService;
};

extern BleSerialLib ArduinoBleSerial;
#endif