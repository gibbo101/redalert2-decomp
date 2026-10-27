// float __fastcall Audio_Event_Type_Get_Rate(AudioEventType *type) -- 0x00405120
// Purpose: returns the type's rate setting (0 while the event system is off).
// @ref __real@4@00000000000000000000=0079a738
#include "shared/audio_event.hpp"

float __fastcall Audio_Event_Type_Get_Rate(AudioEventType *type)
{
    if (Audio_Events_Ready == 0) {
        return 0.0f;
    }
    return type->unknown_54;
}
