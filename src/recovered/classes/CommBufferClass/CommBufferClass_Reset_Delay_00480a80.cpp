// void CommBufferClass::Reset_Delay(bool clear) (0x00480A80)
// Clears the delay statistics, or restarts them from the current mean.
#include "shared/comm_buffer.hpp"

void CommBufferClass::Reset_Delay(bool clear)
{
    if (clear) {
        DelaySum = 0;
        NumDelay = 0;
        MeanDelay = 0;
        MaxDelay = 0;
    } else {
        NumDelay = 1;
        DelaySum = MeanDelay;
        MaxDelay = MeanDelay;
    }
}
