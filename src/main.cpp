#include <Arduino.h>
#include <esp_wifi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_MPU6050.h>
#include "../lib/Adafruit_SGP30/Adafruit_SGP30.h"
#include <Adafruit_BMP280.h>
#include "../lib/Vector/src/Vector.h"
#include "EventLoop/loop.hpp"
#include "EventLoop/Events/events.hpp"
#include "Utils/utils.hpp"
#include "LoRa/lora.hpp"
#include "Debug/debug.hpp"
#include "Config.hpp"


EventLoop *MainThread = new EventLoop();
EventLoop *SecondThread = new EventLoop();
LoRaModule *RadioModule;
Adafruit_AHTX0 AHTSensor;
Adafruit_MPU6050 MPUSensor;
Adafruit_SGP30 SPGSensor;
Adafruit_BMP280 BMPSensor;


void setup()
{
    esp_wifi_set_mode(WIFI_MODE_NULL);
    esp_wifi_stop();
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);
    Utils::PrintLambdaLogo();

    Threading::AppendTask([] () {
        uint16_t secondLastTime = 0;
        while (true)
        {
            secondLastTime = SecondThread->checkLoopTime();
            if (secondLastTime > 20)
                Debug::LOG("[!] Second thread hitch warning: last thread time was " + static_cast<String>(secondLastTime) + "ms");
            SecondThread->loopTick();
        }
    }, 10000);

    RadioModule = new LoRaModule(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_RST, LORA_CS, LORA_DIO0, MainThread, SecondThread);
    delay(200); // si no lo pongo da segfault ¯\_(ツ)_/¯
    if (!RadioModule->Initialize(LoRaModule::Frequencies::EU, static_cast<uint16_t>(500000)/*KHz*/))
        return Debug::LOG("Error while initializing LoRa module");
    Debug::LOG("LoRa module initialized correctly");

    if (!AHTSensor.begin()) 
        return Debug::LOG("Error initializing AHT sensor");
    Debug::LOG("AHT10 module initialized correctly");

    if (!MPUSensor.begin(MPU6050_ADDR)) 
        return Debug::LOG("Error initializing MPU sensor");
    Debug::LOG("MPU module initialized correctly");

    if (!SPGSensor.begin()) 
        return Debug::LOG("Error initializing SPG sensor");
    Debug::LOG("SPG module initialized correctly");

    bool sta = BMPSensor.begin(0x76);
    delay(100);
    if (!sta) 
        return Debug::LOG("Error initializing BME sensor");
    Debug::LOG("BME module initialized correctly");
}

uint16_t lastTime = 0;
void loop () 
{
    lastTime = MainThread->checkLoopTime();
    if (lastTime > 36)
        Debug::LOG("[!] Main thread hitch warning: last thread time was " + static_cast<String>(lastTime) + "ms");
    MainThread->loopTick();
}