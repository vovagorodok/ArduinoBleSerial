#include "BleSerialLibESP32.h"
#ifdef BLE_SERIAL_BLE_LIB_ESP32
#include "BleSerialDummyService.h"

BleSerialLib::BleSerialLib():
    _txCharacteristic(),
    _serialService(&bleSerialDummyService)
{}

void BleSerialLib::begin(const std::string& deviceName)
{
    BLEDevice::init(deviceName);
    auto* server = BLEDevice::createServer();

    begin(server);

    auto* advertising = server->getAdvertising();
    advertising->addServiceUUID(BLE_SERIAL_SERVICE_UUID);
    advertising->setScanResponse(true);
    advertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    advertising->setMaxPreferred(0x12);
    advertising->start();
}

void BleSerialLib::begin(BLEServer* server)
{
    auto* service = server->createService(BLE_SERIAL_SERVICE_UUID);

    auto* rxCharacteristic = service->createCharacteristic(
        BLE_SERIAL_CHARACTERISTIC_UUID_RX,
        BLECharacteristic::PROPERTY_WRITE_NR
    );
    rxCharacteristic->setCallbacks(this);

    auto* txCharacteristic = service->createCharacteristic(
        BLE_SERIAL_CHARACTERISTIC_UUID_TX,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    _txCharacteristic = txCharacteristic;

    auto* advertising = server->getAdvertising();
    service->start();
}

void BleSerialLib::begin(const std::string& deviceName,
                         BleSerialService& serialService)
{
    _serialService = &serialService;
    begin(deviceName);
}

void BleSerialLib::begin(BLEServer* server,
                         BleSerialService& serialService)
{
    _serialService = &serialService;
    begin(server);
}

void BleSerialLib::write(const uint8_t* data, size_t size)
{
    send(data, size);
}

void BleSerialLib::onWrite(BLECharacteristic* characteristic)
{
    auto value = characteristic->getValue();
    auto data = value.data();
    auto size = value.length();

    _serialService->handleData((uint8_t*)data, size);
}

void BleSerialLib::send(const uint8_t* data, size_t size)
{
    if (!_txCharacteristic)
        return;
    _txCharacteristic->setValue((uint8_t*)data, size);
    _txCharacteristic->notify();
}

BleSerialLib ArduinoBleSerial{};
#endif