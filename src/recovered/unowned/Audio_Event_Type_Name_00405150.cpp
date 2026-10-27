// char *__fastcall Audio_Event_Type_Name(AudioEventType *type) -- 0x00405150
// Purpose: returns the type's name ("no events" while the event system is
// off).
#include "shared/audio_event.hpp"

char *__fastcall Audio_Event_Type_Name(AudioEventType *type)
{
    char *name;

    if (Audio_Events_Ready == 0) {
        name = "no events";
    } else {
        name = type->Name;
    }
    return name;
}
