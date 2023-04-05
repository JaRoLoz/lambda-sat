#include <Arduino.h>

#ifndef EVENTS_H
#define EVENTS_H
#include "../../LoRa/lora.hpp"

class EventLoop;

class Event
{
public:
    Event(void* callback);
    virtual ~Event();
    virtual void canBeTriggered(EventLoop *loop);
    unsigned int index;
protected:
    void *_callback;
};

class DelayEvent : public Event
{
public:
    DelayEvent(uint32_t timeout, void* callback);
    void canBeTriggered(EventLoop *loop);
protected:
    uint32_t m_delay;
    uint64_t m_startTime;
};

class IntervalEvent : public DelayEvent
{
public:
    IntervalEvent(uint32_t timeout, void* callback);
    IntervalEvent(uint32_t timeout, void* callback, void* argument);
    void canBeTriggered(EventLoop *loop);
private:
    void* m_argument;
};

#endif