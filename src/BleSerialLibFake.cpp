#include "BleSerialLibFake.h"
#ifdef BLE_SERIAL_BLE_LIB_FAKE

BleSerialLib::BleSerialLib()
{}

bool BleSerialLib::begin(const char* deviceName)
{
    return false;
}

void BleSerialLib::begin()
{}

bool BleSerialLib::begin(const std::string& deviceName)
{
    return false;
}

bool BleSerialLib::begin(BleSerialServerFake* server)
{
    return false;
}

bool BleSerialLib::begin(const char* deviceName,
                         BleSerialService& serialService)
{
    return false;
}

void BleSerialLib::begin(BleSerialService& serialService)
{}

bool BleSerialLib::begin(const std::string& deviceName,
                         BleSerialService& serialService)
{
    return false;
}

bool BleSerialLib::begin(BleSerialServerFake* server,
                         BleSerialService& serialService)
{
    return false;
}

void BleSerialLib::write(const uint8_t* data, size_t size)
{}

void BleSerialLib::send(const uint8_t* data, size_t size)
{}

BleSerialLib ArduinoBleSerial{};
#endif