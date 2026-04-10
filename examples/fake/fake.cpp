#ifndef ARDUINO
#include <ArduinoBleSerial.h>

int main() {
  ArduinoBleSerial.begin("ArduinoBleSerial");
  return 0;
}
#endif