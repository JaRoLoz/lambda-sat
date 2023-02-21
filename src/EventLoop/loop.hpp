#include <Arduino.h>
#include "../../lib/Vector/src/Vector.h"
#include "../Config.hpp"

#ifndef LOOP_H
#define LOOP_H

class Event;

class EventLoop
{
public:
    EventLoop() : eventStack(stackArray) {};
    void addEventListener(Event *event);
    void loopTick();
    uint16_t checkLoopTime();
    Vector<Event*> eventStack;
private:
    Event* stackArray[MAX_EVENT_NUMBER];
    unsigned long m_lastTime = 0;
};

#endif