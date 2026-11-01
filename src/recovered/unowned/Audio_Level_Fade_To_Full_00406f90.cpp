// void __fastcall Audio_Level_Fade_To_Full(AudioLevel *level) -- 0x00406F90
// Purpose: ramps a level to full (0x4000).
#include "shared/audio.hpp"

void __fastcall Audio_Level_Fade_To_Full(AudioLevel *level)
{
    level->Set_Target(0x4000);
}
