#include <Arduino.h>
#include "../Config.hpp"

namespace Debug
{
    void LOG(String data);
    void LOG_VAR(uint64_t data, String name);
    void LOG_VAR(boolean data, String name);
    void LOG_VAR(char data, String name);
    void LOG_VAR(String data, String name);
}