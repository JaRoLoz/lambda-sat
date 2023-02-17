#include "async.hpp"

AsyncTimeoutTask::AsyncTimeoutTask(uint16_t timeout, void* callback)
{
    reinterpret_cast<void (*)()>(callback)();
    delay(2000);
    delete this;
}

AsyncTimeoutTask::~AsyncTimeoutTask()
{
    Serial.println("Destructor called");
}