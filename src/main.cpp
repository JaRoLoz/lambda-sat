#include <Arduino.h>
#include <esp_wifi.h>
#include "../lib/Vector/src/Vector.h"
#include "EventLoop/loop.hpp"
#include "EventLoop/Events/events.hpp"
#include "LoRa/lora.hpp"
#include "Debug/debug.hpp"
#include "Config.hpp"

EventLoop *MainThread = new EventLoop();

void setup()
{
    esp_wifi_set_mode(WIFI_MODE_NULL);
    esp_wifi_stop();
    Serial.begin(115200);
    Debug::LOG("Initializing...");
}

uint16_t lastTime = 0;
void loop () 
{
    lastTime = MainThread->checkLoopTime();
    if (lastTime > 29) 
        Debug::LOG("[!] Thread hitch warning: last thread time was " + static_cast<String>(lastTime) + "ms");
    MainThread->loopTick();
}














// void loop()
// {
    // Serial.println(analogRead(A0));
    // if (loraTransmitter->serialPort.available())
    // {
    //     Debug::LOG("Incoming serial");
    //     String serialString = loraTransmitter->serialPort.readString();
    //     if (serialString.indexOf(loraTransmitter->carrierCode) != -1)
    //     {
    //         while (serialString.indexOf(loraTransmitter->carrierCode) != -1)
    //         {
    //             serialString.remove(0, serialString.indexOf(loraTransmitter->carrierCode));
    //             String tempString;
    //             for (int i = 0; i < serialString.indexOf('\n'); i++)
    //                 tempString += serialString[i];
    //             serialString.remove(0, 4);
    //             loraTransmitter->HandleSerial(serialString);
    //         }
    //     }
    // }
// }