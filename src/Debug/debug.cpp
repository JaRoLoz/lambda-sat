#include "debug.hpp"

namespace Debug
{
    void LOG(String data)
    {
        if (DEBUG)
            Serial.println("# Debug Log: " + data);
    }
    void LOG_VAR(uint64_t data, String name)
    {
        if (DEBUG)
            Serial.println("# Debug Variable Log: name: " + name + "    value: " + data);
    }
    void LOG_VAR(boolean data, String name)
    {
        if (DEBUG)
            Serial.println("# Debug Variable Log: name: " + name + "    value: " + data);
    }
    void LOG_VAR(char data, String name)
    {
        if (DEBUG)
            Serial.println("# Debug Variable Log: name: " + name + "    value: " + String(data));
    }
    void LOG_VAR(String data, String name)
    {
        if (DEBUG)
            Serial.println("# Debug Variable Log: name: " + name + "    value: " + data);
    }
}