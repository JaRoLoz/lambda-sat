#include "lora.hpp"

LoRaModule::LoRaModule(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t rst, uint8_t nss, uint8_t dio0, EventLoop *mainThread, EventLoop *secondThread)
{
    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);  // puta vida tete
    LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO0);          // puta vida tete x2
    this->m_mainThread = mainThread;
    this->m_secondThread = secondThread;
}

bool LoRaModule::Initialize(uint16_t frequency, uint16_t bandwidth)
{
    if (!LoRa.begin(frequency)) 
    {
        Debug::LOG("Error initializing LoRa module");
        return false;
    }

    LoRa.setSyncWord(LORA_SYNCWORD);
    LoRa.setSignalBandwidth(bandwidth);
    LoRa.setSpreadingFactor(12);
    LoRa.setCodingRate4(5);
    LoRa.setPreambleLength(8);

    this->m_secondThread->addEventListener(new IntervalEvent(0, reinterpret_cast<void*>(&LoRaModule::ParseLoraPacket))); // el que tenga miedo a morir que no nazca

    return true;
}

void LoRaModule::RouteMethod(unsigned int route, void *method)
{
    this->m_methods[route] = method;
}

void LoRaModule::ParseLoraPacket()
{
    unsigned int packetSize = LoRa.parsePacket();
    if (packetSize < 1) 
        return;
    
    byte _buffer[LoRa.available()];
    for (size_t i = 0; i < LoRa.available(); i++)
        _buffer[i] = LoRa.read();
    unsigned int *buffer = reinterpret_cast<unsigned int*>(_buffer);
    Debug::LOG(static_cast<String>(buffer[0]));
    // int state = this->m_module->receive(buffer, sizeof(buffer));
    // if (state != RADIOLIB_ERR_NONE)
    //     return;

    // if (this->m_module->getPacketLength() < 1)
    //     return;
    
    // uint index = (uint)buffer[0];
    // if (index > LORA_RX_MESSAGES)  // por si algún pussy lo intenta
    //     return;

    // void* method = this->m_methods[index];
    // if (method)
    //     ((void (*)(void)) method)(); // el que tenga miedo a morir que no nazca
}
