#include "events.hpp"
#include "../loop.hpp"
#include "../../Debug/debug.hpp"

Event::Event(void *callback)
{
    this->_callback = callback;
}

DelayEvent::DelayEvent(uint32_t timeout, void* callback) : Event(callback)
{
    this->_callback = callback;
    this->m_startTime = millis();
    this->m_delay = timeout;
}

IntervalEvent::IntervalEvent(uint32_t timeout, void* callback) : DelayEvent(timeout, callback)
{
    this->_callback = callback;
    this->m_startTime = millis();
    this->m_delay = timeout;
}

Event::~Event() 
{
    Debug::LOG("Event destructor called.");
    Debug::LOG_VAR(static_cast<uint64_t>(xPortGetFreeHeapSize()), "Free heap size");
}

void Event::canBeTriggered(EventLoop *loop)
{
    reinterpret_cast<void (*)(EventLoop*, unsigned int, Event*)>(this->_callback)(loop, this->index, this);
}

void DelayEvent::canBeTriggered(EventLoop *loop)
{
    if ((millis() - this->m_startTime) >= this->m_delay) {
        reinterpret_cast<void (*)(EventLoop*, unsigned int, Event*)>(this->_callback)(loop, this->index, this);
        delete this;
        loop->removeEvent(this->index);
    }
}

void IntervalEvent::canBeTriggered(EventLoop *loop)
{
    if ((millis() - this->m_startTime) >= this->m_delay)
    {
        reinterpret_cast<void (*)(EventLoop*, unsigned int, Event*)>(this->_callback)(loop, this->index, this);
        this->m_startTime = millis();
    }
}