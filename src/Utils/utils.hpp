#ifndef UTILS_H
#define UTILS_H
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "../Config.hpp"

namespace Utils
{
    void PrintLambdaLogo();
    String GenerateRandomString(int length);
    String IntToBase36(uint32_t num);
    float f_Sqrt(float number);
}

namespace Threading
{
    template <typename Function>
    void AppendTask(Function func, const size_t stackSize)
    {
        xTaskCreatePinnedToCore(
            [](void *parameter)
            {
                auto f = static_cast<Function *>(parameter);
                (*f)();
                delete f;
                vTaskDelete(nullptr);
            },
            "TaskOnCore2",
            stackSize,
            new Function{func},
            0,
            nullptr,
            0
        );
    }
}

#endif
