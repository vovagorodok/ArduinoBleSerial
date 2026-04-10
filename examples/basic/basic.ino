#include <ArduinoBleSerial.h>
#include "../MySerialService.h"

#ifdef BLE_SERIAL_LOGS
#ifndef ARDUINO_ARCH_ESP32
extern "C" {
int _write(int fd, char *ptr, int len) {
  (void) fd;
  return Serial.write(ptr, len);
}
}
#endif
#endif

MySerialService serialService{};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  ArduinoBleSerial.begin("ArduinoBleSerial", serialService);
}

void loop() {
#ifdef BLE_SERIAL_LIB_ARDUINO_BLE
  BLE.poll();
#endif
  serialService.checkSerialData();
}