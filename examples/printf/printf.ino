#include <ArduinoBleSerial.h>
#include <ArduinoBleSerialPrintf.h>
#include <cstdio>

void setup() {
  Serial.begin(115200);
  while (!Serial);

  ArduinoBleSerial.begin("ArduinoBleSerial");
  setupBlePrintf();
}

void loop() {
#ifdef BLE_SERIAL_LIB_ARDUINO_BLE
  BLE.poll();
#endif
  printf("printf\n");
  delay(1000);
}