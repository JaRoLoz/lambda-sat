#ifndef UTILS_H
#define UTILS_H
#include <Arduino.h>
#include "../Config.hpp"

namespace Utils
{
    String GenerateRandomString(int length);
    String IntToBase36(uint32_t num);
    float f_Sqrt(float number);
}

// namespace Threading
// {
//     typedef struct TaskParams
//     {
//         String taskName;
//         unsigned int taskPriority;
//         unsigned int taskCore;
//         TaskFunction_t coreFunction;
//     };
//     void AppendTask(TaskParams params);
// }

#endif
