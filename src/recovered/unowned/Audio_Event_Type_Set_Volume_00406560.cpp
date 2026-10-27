// void __fastcall Audio_Event_Type_Set_Volume(AudioEventType *type, int volume) -- 0x00406560
// Purpose: sets the type's own volume level at once.
#include "shared/audio_event.hpp"

void __fastcall Audio_Event_Type_Set_Volume(AudioEventType *type, int volume)
{
    type->VolumeLevel.Set(volume);
    type->VolumeLevel.Update();
}
