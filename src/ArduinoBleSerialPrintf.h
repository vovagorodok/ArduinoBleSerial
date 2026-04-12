#pragma once
#include <ArduinoBleSerial.h>

#ifdef ARDUINO_ARCH_ESP32
static ssize_t _writeBle(void* cookie, const char* buf, size_t size) {
  static char buffer[BLE_SERIAL_MAX_BUFFER_SIZE];
  static size_t pos = 0;

  for (size_t i = 0; i < size; i++) {
    const char c = buf[i];
    buffer[pos++] = c;

    if (c == '\n' || pos >= BLE_SERIAL_MAX_BUFFER_SIZE) {
      ArduinoBleSerial.write(reinterpret_cast<const uint8_t*>(buffer), pos);
      pos = 0;
    }
  }

  return size;
}

inline void setupBlePrintf() {
  static cookie_io_functions_t funcs = {
    .read  = nullptr,
    .write = _writeBle,
    .seek  = nullptr,
    .close = nullptr,
  };
  FILE* file = fopencookie(nullptr, "w", funcs);
  if (file != nullptr) {
    setvbuf(file, nullptr, _IONBF, 0);
    stdout = file;
    stderr = file;
  }
}
#else
extern "C" int _write(int fd, const char *ptr, int len) {
  (void) fd;
  ArduinoBleSerial.write(reinterpret_cast<const uint8_t*>(ptr), len);
  return len;
}

inline void setupBlePrintf()
{}
#endif