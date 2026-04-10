#pragma once
#include "BleSerialDefinesArduino.h"

#ifdef BLE_SERIAL_LOGS
    #if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
        #define BLE_SERIAL_PRINTF Serial.printf
    #else
        #define BLE_SERIAL_PRINTF printf
    #endif

    #define BLE_SERIAL_LOG(tag, fmt, ...) \
        BLE_SERIAL_PRINTF("DBG: BleSerial: " tag ": " fmt "\n", ##__VA_ARGS__)
#else
    #define BLE_SERIAL_LOG(fmt, ...) \
        do {} while (0)
#endif