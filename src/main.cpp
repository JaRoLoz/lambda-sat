//#include "../lib/Eventually/src/Eventually.h"
#include "../lib/Vector/src/Vector.h"
#include "EventLoop/loop.hpp"
#include "LoRa/lora.hpp"
#include "Async/async.hpp"
#include "Debug/debug.hpp"
#include "Config.hpp"

LoRa *loraTransmitter = new LoRa(LORA_RX, LORA_TX);
EventLoop *MainThread = new EventLoop();

void setup()
{
    Serial.begin(115200);
    Debug::LOG("Initializing...");
    // loraTransmitter->Initialize();
    // Debug::LOG("Lora started!");
    // loraTransmitter->TransmitMessage(LoRa::Transmitions::diagnostics, "holis");
    AsyncTimeoutTask *task = new AsyncTimeoutTask(1000, reinterpret_cast<void*>(*[] () {
        Debug::LOG("Executed!!!");
    }));
    MainThread->addEventListener(new Event(reinterpret_cast<void*>(*[] () {
        Debug::LOG("Task ran!!!");
    })));
}

void loop () 
{ 
    
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