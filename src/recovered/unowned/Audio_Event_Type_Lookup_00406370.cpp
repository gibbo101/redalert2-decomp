// AudioEventType *__fastcall Audio_Event_Type_Lookup(char const *name) -- 0x00406370
// The event type with this name, or 0 (unreferenced; Audio_Event_Type_Find 0x004063C0 makes a
// missing one instead).
// @ref __stricmp=00781f20
#include "shared/crt_memory.hpp"
#include "shared/audio_event.hpp"
#include "shared/crt_string.hpp"

AudioEventType *__fastcall Audio_Event_Type_Lookup(char const *name)
{
    AudioEventType *type;

    if (Audio_Events_Ready == 0) {
        return 0;
    }
    type = (AudioEventType *)Audio_List_First(&Audio_Event_Type_List);
    while (type != 0) {
        if (_stricmp(name, type->Name) == 0) {
            return type;
        }
        type = (AudioEventType *)Audio_List_Next(type);
    }
    return 0;
}
