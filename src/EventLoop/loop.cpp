#include "loop.hpp"

Event::Event(void *callback)
{
    this->_callback = callback;
}

void Event::canBeTriggered(unsigned int index)
{
    reinterpret_cast<void (*)(unsigned int)>(this->_callback)(index);
}

EventLoop::EventLoop() {}

void EventLoop::addEventListener(Event *event) 
{
    event->index = this->eventStack.size() + 1;
    this->eventStack.push_back(event);
}