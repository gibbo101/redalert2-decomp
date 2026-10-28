// void __fastcall Audio_Wait_Drain(AudioLevel *level) -- 0x00406FE0
// Purpose: calls 0x00481FB0 until the level has reached its target or its
// time limit (now plus level->MaxElapsed) has passed. Do_Lose-like scenario
// ends (0x0065E590) fade the global volume level to zero and wait here.
#include "shared/audio.hpp"

void unknown_00481fb0();            // 0x00481FB0

void __fastcall Audio_Wait_Drain(AudioLevel *level)
{
    __int64 end = Audio_Now() + level->MaxElapsed;

    while (level->Current != level->Target) {
        if ((unsigned __int64)Audio_Now() >= (unsigned __int64)end) {
            return;
        }
        unknown_00481fb0();
    }
}
