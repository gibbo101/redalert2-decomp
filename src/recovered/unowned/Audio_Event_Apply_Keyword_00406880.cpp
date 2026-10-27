// int __fastcall Audio_Event_Apply_Keyword(unsigned int *flags, char const *name) -- 0x00406880
// Purpose: looks the keyword up in the table and, when there are flags to
// change, turns its flags on (dropping the group it replaces: 0x60 or 0xC00).
// Returns whether the keyword exists.
// @ref __stricmp=00781f20
#include "shared/audio_event.hpp"

extern "C" int __cdecl _stricmp(char const *left, char const *right);

int __fastcall Audio_Event_Apply_Keyword(unsigned int *flags, char const *name)
{
    AudioEventKeyword *entry = Audio_Event_Keywords;

    while (entry->Name != 0 && _stricmp(name, entry->Name) != 0) {
        entry++;
    }
    if (flags != 0) {
        if (entry->Flags & 0x60) {
            *flags &= ~0x60;
        } else if (entry->Flags & 0xc00) {
            *flags &= ~0xc00;
        }
        *flags |= entry->Flags;
    }
    return entry->Name != 0;
}
