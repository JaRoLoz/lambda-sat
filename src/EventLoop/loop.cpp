#include "loop.hpp"
#include "Events/events.hpp"
#include "../Debug/debug.hpp"

void EventLoop::addEventListener(Event *event) 
{
    event->index = this->eventStack.size();
    this->eventStack.push_back(event);
}

void EventLoop::loopTick() 
{
    for (size_t i = 0; i < this->eventStack.size(); i++)
        eventStack.at(i)->canBeTriggered(this);
}

void EventLoop::removeEvent(unsigned int index) 
{
    for (size_t i = index + 1; i < this->eventStack.size(); i++)
        eventStack.at(i)->index--;
    this->eventStack.remove(index);
}

uint16_t EventLoop::checkLoopTime() 
{
    uint16_t _delay = millis() - this->m_lastTime;
    this->m_lastTime = millis();
    return _delay;
}