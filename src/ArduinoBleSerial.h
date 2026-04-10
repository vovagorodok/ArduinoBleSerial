#pragma once
#include "BleSerialDefines.h"
#if defined(BLE_SERIAL_BLE_LIB_ARDUINO_BLE)
#include "BleSerialLibArduinoBle.h"
#elif defined(BLE_SERIAL_BLE_LIB_NIM_BLE_ARDUINO)
#include "BleSerialLibNimBleArduino.h"
#elif defined(BLE_SERIAL_BLE_LIB_ESP32)
#include "BleSerialLibESP32.h"
#elif defined(BLE_SERIAL_BLE_LIB_FAKE)
#include "BleSerialLibFake.h"
#else
#error "Unsupported BLE library."
#endif