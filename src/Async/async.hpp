#ifndef ASYNC_H
#define ASYNC_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Hash.h>
#include "utils/utils.hpp"
#include "../Debug/debug.hpp"
#include "../Config.hpp"

class AsyncTimeoutTask
{
public:
    AsyncTimeoutTask(uint16_t timeout, void* callback);
    ~AsyncTimeoutTask();

private:
    uint8_t _timeout = 0;
    uint64_t _millis = 0;
    void* _callback;
};

#endif