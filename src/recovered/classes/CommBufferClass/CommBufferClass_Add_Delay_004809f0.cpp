// void CommBufferClass::Add_Delay(unsigned long delay) (0x004809F0)
// Folds a round-trip delay into the running mean (a 256-sample window once
// full, rounded) and the maximum.
#include "shared/comm_buffer.hpp"

void CommBufferClass::Add_Delay(unsigned long delay)
{
    int roundup = 0;
    if (NumDelay == 256) {
        DelaySum += delay - MeanDelay;
        if ((DelaySum & 0xff) > 127) {
            roundup = 1;
        }
        MeanDelay = (DelaySum >> 8) + roundup;
    } else {
        NumDelay++;
        DelaySum += delay;
        MeanDelay = DelaySum / NumDelay;
    }
    if (delay > MaxDelay) {
        MaxDelay = delay;
    }
}
