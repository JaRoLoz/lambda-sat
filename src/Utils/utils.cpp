#include "utils.hpp"

const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

namespace Utils
{
    String GenerateRandomString(int length)
    {
        String randomString = "";
        for (int i = 0; i < length; i++)
        {
            randomString += characters[random(sizeof(characters) - 1)];
        }
        return randomString;
    }
    String IntToBase36(uint32_t num)
    {
        char base36Buffer[5];
        int pos = 0;
        for (int i = 0; i < 4; i++)
        {
            int remainder = num % 36;
            base36Buffer[pos++] = (remainder < 10) ? ('0' + remainder) : ('a' + remainder - 10);
            num /= 36;
        }
        base36Buffer[pos] = '\0';
        char base36Encoded[5];
        for (int i = 0; i < 4; i++)
        {
            base36Encoded[i] = base36Buffer[3 - i];
        }
        base36Encoded[4] = '\0';
        return base36Encoded;
    }
    float f_Sqrt(float number) // gracias carmack ;)
    {
        long i;
        float x2, y;

        x2 = number * 0.5F;
        y = number;
        i = *(long *)&y;
        i = 0x5f3759df - (i >> 1);
        y = *(float *)&i;
        y = y * (1.5F - (x2 * y * y));
        y = y * (1.5F - (x2 * y * y));

        return 1 / y;
    }
}

// namespace Threading
// {
//     void AppendTask(Threading::TaskParams params)
//     {
//         xTaskCreatePinnedToCore(params.coreFunction, params.taskName.c_str(), uxTaskGetStackHighWaterMark(params.coreFunction));
//     }
// }
