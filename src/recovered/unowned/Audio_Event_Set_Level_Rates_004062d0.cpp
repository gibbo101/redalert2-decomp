// void __fastcall Audio_Event_Set_Level_Rates(AudioEvent *event, __int64 period) -- 0x004062D0
// Purpose: makes the event's volume, frequency and pan levels ramp over a full
// step (0x4000) per period milliseconds.
// @ref ?Set_Rate@AudioLevel@@QAIX_JH@Z=004070d0
#include "shared/audio_event.hpp"

void __fastcall Audio_Event_Set_Level_Rates(AudioEvent *event, __int64 period)
{
    event->Levels.Volume.Set_Rate(period, 0x4000);
    event->Levels.Frequency.Set_Rate(period, 0x4000);
    event->Levels.Pan.Set_Rate(period, 0x4000);
}
