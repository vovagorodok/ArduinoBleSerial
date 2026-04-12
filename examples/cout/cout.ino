#include <ArduinoBleSerial.h>
#include <ArduinoBleSerialCout.h>
#include <iostream>

void setup() {
  Serial.begin(115200);
  while (!Serial);

  ArduinoBleSerial.begin("ArduinoBleSerial");
  setupBleCout();
}

void loop() {
#ifdef BLE_SERIAL_LIB_ARDUINO_BLE
  BLE.poll();
#endif
  std::cout << "cout" << std::endl;
  delay(1000);
}