#include "BleSerialLibNimBleArduino.h"
#ifdef BLE_SERIAL_BLE_LIB_NIM_BLE_ARDUINO
#include "BleSerialDummyService.h"

BleSerialLib::BleSerialLib():
    _txCharacteristic(),
    _serialService(&bleSerialDummyService)
{}

bool BleSerialLib::begin(const std::string& deviceName)
{
    BLEDevice::init(deviceName);
    auto* server = BLEDevice::createServer();

    if(!begin(server))
        return false;

    auto* advertising = server->getAdvertising();
    advertising->addServiceUUID(BLE_SERIAL_SERVICE_UUID);
#ifdef BLE_SERIAL_BLE_LIB_NIM_BLE_ARDUINO_V1
    advertising->setScanResponse(true);
    advertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    advertising->setMaxPreferred(0x12);
#endif
    return advertising->start();
}

bool BleSerialLib::begin(BLEServer* server)
{
    auto* service = server->createService(BLE_SERIAL_SERVICE_UUID);

    auto* rxCharacteristic = service->createCharacteristic(
        BLE_SERIAL_CHARACTERISTIC_UUID_RX,
        NIMBLE_PROPERTY::WRITE_NR
    );
    rxCharacteristic->setCallbacks(this);

    auto* txCharacteristic = service->createCharacteristic(
        BLE_SERIAL_CHARACTERISTIC_UUID_TX,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    _txCharacteristic = txCharacteristic;

    return service->start();
}

bool BleSerialLib::begin(const std::string& deviceName,
                         BleSerialService& serialService)
{
    _serialService = &serialService;
    return begin(deviceName);
}

bool BleSerialLib::begin(BLEServer* server,
                         BleSerialService& serialService)
{
    _serialService = &serialService;
    return begin(server);
}

void BleSerialLib::write(const uint8_t* data, size_t size)
{
    send(data, size);
}

#ifdef BLE_SERIAL_BLE_LIB_NIM_BLE_ARDUINO_V1
void BleSerialLib::onWrite(BLECharacteristic* characteristic)
#else
void BleSerialLib::onWrite(BLECharacteristic* characteristic, BLEConnInfo& connInfo)
#endif
{
    auto value = characteristic->getValue();
    auto data = value.data();
    auto size = value.length();

    _serialService->handleData(data, size);
}

void BleSerialLib::send(const uint8_t* data, size_t size)
{
    _txCharacteristic->setValue(data, size);
    _txCharacteristic->notify();
}

BleSerialLib ArduinoBleSerial{};
#endif