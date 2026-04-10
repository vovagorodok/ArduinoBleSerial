#include "BleSerialService.h"
#include "ArduinoBleSerial.h"
#include "BleSerialLogger.h"

namespace
{
#define TAG "Service"
}

void BleSerialService::handleData(const uint8_t* data, size_t size)
{
    BLE_SERIAL_LOG(TAG, "%.*s", (int)size, (const char*)data);
}

void BleSerialService::sendData(const uint8_t* data, size_t size)
{
    ArduinoBleSerial.write(data, size);
}