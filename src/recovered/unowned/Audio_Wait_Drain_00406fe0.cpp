// void __fastcall Audio_Wait_Drain(AudioDrainWait *wait) -- 0x00406FE0
// Purpose: calls 0x00481FB0 until the two counters match or the time limit
// (now plus wait->Limit) has passed.
#include "shared/audio.hpp"

struct AudioDrainWait {
    int unknown_00;
    int Pending;                    // +0x04
    int Done;                       // +0x08
    int unknown_0c;
    __int64 Limit;                  // +0x10 ticks
};

void unknown_00481fb0();            // 0x00481FB0

void __fastcall Audio_Wait_Drain(AudioDrainWait *wait)
{
    __int64 end = Audio_Now() + wait->Limit;

    while (wait->Pending != wait->Done) {
        if ((unsigned __int64)Audio_Now() >= (unsigned __int64)end) {
            return;
        }
        unknown_00481fb0();
    }
}
