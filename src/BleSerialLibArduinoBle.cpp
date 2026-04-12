#include "BleSerialLibArduinoBle.h"
#ifdef BLE_SERIAL_BLE_LIB_ARDUINO_BLE
#include "BleSerialDummyService.h"

namespace
{
BLEService service(BLE_SERIAL_SERVICE_UUID);
BLECharacteristic rxCharacteristic(BLE_SERIAL_CHARACTERISTIC_UUID_RX, BLEWriteWithoutResponse, BLE_SERIAL_MAX_BUFFER_SIZE);
BLECharacteristic txCharacteristic(BLE_SERIAL_CHARACTERISTIC_UUID_TX, BLERead | BLENotify, BLE_SERIAL_MAX_BUFFER_SIZE);
}

BleSerialLib::BleSerialLib():
    _serialService(&bleSerialDummyService)
{}

bool BleSerialLib::begin(const char* deviceName)
{
    if (!BLE.begin())
        return false;

    BLE.setLocalName(deviceName);
    BLE.setDeviceName(deviceName);

    begin();

    return BLE.setAdvertisedService(service) and BLE.advertise();
}

void BleSerialLib::begin()
{
    service.addCharacteristic(rxCharacteristic);
    service.addCharacteristic(txCharacteristic);
    rxCharacteristic.setEventHandler(BLEWritten, onWrite);

    BLE.addService(service);
}

bool BleSerialLib::begin(const char* deviceName,
                         BleSerialService& serialService)
{
    _serialService = &serialService;
    return begin(deviceName);
}

void BleSerialLib::begin(BleSerialService& serialService)
{
    _serialService = &serialService;
    begin();
}

void BleSerialLib::write(const uint8_t* data, size_t size)
{
    send(data, size);
}

void BleSerialLib::onWrite(const BLECharacteristic& characteristic)
{
    _serialService->handleData(
        rxCharacteristic.value(),
        rxCharacteristic.valueLength());
}

void BleSerialLib::send(const uint8_t* data, size_t size)
{
    txCharacteristic.setValue(data, size);
}

void BleSerialLib::onWrite(BLEDevice central, BLECharacteristic characteristic)
{
    ArduinoBleSerial.onWrite(characteristic);
}

BleSerialLib ArduinoBleSerial{};
#endif