#pragma once
#include <ArduinoBleSerial.h>
#include <iostream>

class BleSerialStreambuf : public std::streambuf {
protected:
  int overflow(int c) override {
    if (c == EOF) return EOF;
    write(static_cast<char>(c));
    return c;
  }

  std::streamsize xsputn(const char* s, std::streamsize n) override {
    for (std::streamsize i = 0; i < n; i++) {
      write(s[i]);
    }
    return n;
  }

private:
  inline void write(char c) {
    buffer[pos++] = c;
    if (c == '\n' || pos >= BLE_SERIAL_MAX_BUFFER_SIZE) {
      ArduinoBleSerial.write(reinterpret_cast<const uint8_t*>(buffer), pos);
      pos = 0;
    }
  }

  char buffer[BLE_SERIAL_MAX_BUFFER_SIZE];
  size_t pos = 0;
};

inline void setupBleCout() {
  static BleSerialStreambuf streambuf{};
  std::cout.rdbuf(&streambuf);
}