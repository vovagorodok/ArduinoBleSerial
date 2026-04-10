#pragma once
#include "BleSerialDefinesArduino.h"

class BleSerialService
{
public:
    virtual void handleData(const uint8_t* data, size_t size);
    virtual ~BleSerialService() = default;

protected:
    void sendData(const uint8_t* data, size_t size);
};