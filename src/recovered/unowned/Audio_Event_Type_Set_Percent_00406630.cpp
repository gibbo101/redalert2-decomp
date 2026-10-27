// void __fastcall Audio_Event_Type_Set_Percent(AudioEventType *type, int percent) -- 0x00406630
// Purpose: sets the +0x68 setting of the type, kept within 0..100.
#include "shared/audio_event.hpp"

void __fastcall Audio_Event_Type_Set_Percent(AudioEventType *type, int percent)
{
    if (percent > 100) {
        percent = 100;
    } else if (percent < 0) {
        percent = 0;
    }
    type->unknown_68 = percent;
}
