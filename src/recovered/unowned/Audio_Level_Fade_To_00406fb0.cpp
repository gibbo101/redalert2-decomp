// void __fastcall Audio_Level_Fade_To(AudioLevel *level, int value) -- 0x00406FB0
// Purpose: ramps a level towards value (Set_Target 0x004070A0 as a tail
// call). No callers in the executable, like Fade_To_Full 0x00406F90.
// @ref ?Set_Target@AudioLevel@@QAIXH@Z=004070a0
#include "shared/audio.hpp"

void __fastcall Audio_Level_Fade_To(AudioLevel *level, int value)
{
    level->Set_Target(value);
}
