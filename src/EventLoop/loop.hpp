#include "../../lib/Vector/src/Vector.h"
#include "../Config.hpp"

#ifndef LOOP_H
#define LOOP_H

class Event
{
public:
    Event(void* callback);
    virtual ~Event();
    virtual void canBeTriggered(unsigned int index);
    unsigned int index;
private:
    void *_callback;
};

class EventLoop
{
public:
    EventLoop();
    void addEventListener(Event *event);
private:
    Event stackArray[MAX_EVENT_NUMBER];
    Vector<Event*> eventStack(Event*);
};

#endif