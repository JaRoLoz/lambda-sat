#ifndef LORA__H
#define LORA__H

#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include "../Utils/utils.hpp"
#include "../Debug/debug.hpp"
#include "../EventLoop/loop.hpp"
#include "../EventLoop/Events/events.hpp"
#include "../Config.hpp"

class LoRaModule
{
public:
    enum Frequencies
    {
        EU = 867,
        US = 912,
        AU = 920,
        AS = 923
    };
    LoRaModule(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t rst, uint8_t nss, uint8_t dio0, EventLoop *mainThread, EventLoop *secondThread);
    bool Initialize(uint16_t frequency, uint16_t bandwidth);
    void RouteMethod(unsigned int route, void *method);
    static void ParseLoraPacket();

protected:
    EventLoop *m_mainThread;
    EventLoop *m_secondThread;
    void *m_methods[LORA_RX_MESSAGES];
};

#endif