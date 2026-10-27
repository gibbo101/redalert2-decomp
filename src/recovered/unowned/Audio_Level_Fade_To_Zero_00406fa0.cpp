// void __fastcall Audio_Level_Fade_To_Zero(AudioLevel *level) -- 0x00406FA0
// Purpose: ramps a level down to nothing.
#include "shared/audio.hpp"

void __fastcall Audio_Level_Fade_To_Zero(AudioLevel *level)
{
    level->Set_Target(0);
}
