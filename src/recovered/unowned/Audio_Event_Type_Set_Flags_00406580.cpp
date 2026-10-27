// void __fastcall Audio_Event_Type_Set_Flags(AudioEventType *type, unsigned int flags) -- 0x00406580
// Purpose: sets the type's flags; the intro and outro counts follow the
// flags that need them (at least 1 when set, 0 when not).
#include "shared/audio_event.hpp"

void __fastcall Audio_Event_Type_Set_Flags(AudioEventType *type, unsigned int flags)
{
    type->Flags = flags;
    if (flags & 0x20) {
        if (type->Intro == 0) {
            type->Intro = 1;
        }
    } else {
        type->Intro = 0;
    }
    if (flags & 0x40) {
        if (type->Outro == 0) {
            type->Outro = 1;
        }
    } else {
        type->Outro = 0;
    }
}
