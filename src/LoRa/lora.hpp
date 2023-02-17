#ifndef LORA_H
#define LORA_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Hash.h>
#include "utils/utils.hpp"
#include "../Debug/debug.hpp"
#include "../Config.hpp"

class LoRa
{
public:
    enum Transmitions
    {
        errorcheck = 0,
        diagnostics = 1,
        gyroscope = 2,
        accelerometer = 3,
        magnetometer = 4,
        rawSensorData = 5
    };
    SoftwareSerial serialPort;
    String carrierCode;
    LoRa(unsigned int rx, unsigned int tx);
    void Initialize();
    boolean TransmitMessage(Transmitions transmitionType, String data);
    void HandleSerial(String data);

private:
    uint32_t messageIndex = 0;
};

#endif