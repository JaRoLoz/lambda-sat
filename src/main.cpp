#include <Arduino.h>
#include <esp_wifi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_SGP30.h>
#include <FS.h>
#include <LITTLEFS.h>
// #include <esp_camera.h>
#include <Vector.h>
#include "EventLoop/loop.hpp"
#include "EventLoop/Events/events.hpp"
#include "Utils/utils.hpp"
#include "LoRa/lora.hpp"
#include "Debug/debug.hpp"
#include "Config.hpp"


TwoWire I2CBus = TwoWire(0);
EventLoop *MainThread = new EventLoop();
EventLoop *SecondThread = new EventLoop();
LoRaModule *RadioModule;
Adafruit_AHTX0 AHTSensor;
Adafruit_MPU6050 MPUSensor;
Adafruit_SGP30 SPGSensor;
Adafruit_BMP085 BMPSensor;


void setup()
{
    esp_wifi_set_mode(WIFI_MODE_NULL);
    esp_wifi_stop();
    Serial.begin(115200);
    I2CBus.begin(SDA_PIN, SCL_PIN, 100000);
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

    if(!LITTLEFS.begin())
        return Debug::LOG("Error while initializing LittleFS");
    Debug::LOG("LittleFS initialized correctly");

    RadioModule = new LoRaModule(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_RST, LORA_CS, LORA_DIO0, MainThread, SecondThread);
    delay(200); // si no lo pongo da segfault ¯\_(ツ)_/¯
    if (!RadioModule->Initialize(LoRaModule::Frequencies::EU, static_cast<uint16_t>(500000)/*KHz*/))
        return Debug::LOG("Error while initializing LoRa module");
    Debug::LOG("LoRa module initialized correctly");

    if (!AHTSensor.begin(&I2CBus)) 
        return Debug::LOG("Error initializing AHT sensor");
    Debug::LOG("AHT10 module initialized correctly");

    if (!MPUSensor.begin(MPU6050_ADDR, &I2CBus)) 
        return Debug::LOG("Error initializing MPU sensor");
    MPUSensor.setAccelerometerRange(MPU6050_RANGE_8_G);
    MPUSensor.setGyroRange(MPU6050_RANGE_500_DEG);
    MPUSensor.setFilterBandwidth(MPU6050_BAND_21_HZ);

    Debug::LOG("MPU module initialized correctly");

    if (!SPGSensor.begin(&I2CBus)) 
        return Debug::LOG("Error initializing SPG sensor");
    Debug::LOG("SPG module initialized correctly");

    if (!BMPSensor.begin(BMP180_ADDR, &I2CBus))
        return Debug::LOG("Error initializing BMP sensor");
    Debug::LOG("BMP module initialized correctly");

    MainThread->addEventListener(new IntervalEvent(100, reinterpret_cast<void *>(* [] () {
        SPGSensor.IAQmeasure();
        Debug::LOG((String) SPGSensor.eCO2);
    })));
    MainThread->addEventListener(new IntervalEvent(100, reinterpret_cast<void *>(* [] () {
        
    })));
    MainThread->addEventListener(new IntervalEvent(100, reinterpret_cast<void *>(* [] () {
        
    })));
    MainThread->addEventListener(new IntervalEvent(100, reinterpret_cast<void *>(* [] () {
        
    })));
    MainThread->addEventListener(new IntervalEvent(100, reinterpret_cast<void *>(* [] () {
        
    })));
    MainThread->addEventListener(new IntervalEvent(100, reinterpret_cast<void *>(* [] () {
        
    })));
    MainThread->addEventListener(new IntervalEvent(100, reinterpret_cast<void *>(* [] () {
        
    })));
    MainThread->addEventListener(new IntervalEvent(100, reinterpret_cast<void *>(* [] () {
        
    })));
    MainThread->addEventListener(new IntervalEvent(1000, reinterpret_cast<void *>(* [] () {
        Debug::LOG_VAR(static_cast<uint64_t>(xPortGetFreeHeapSize()), "Free heap size");
    })));
}

uint16_t lastTime = 0;
void loop () 
{
    lastTime = MainThread->checkLoopTime();
    if (lastTime > 36)
        Debug::LOG("[!] Main thread hitch warning: last thread time was " + static_cast<String>(lastTime) + "ms");
    MainThread->loopTick();
}