// void __fastcall Audio_Event_Play_Named(char const *name, int volume) -- 0x00406680
// Purpose: starts an event of the type with this name and sets its volume
// (volume is in 1/256ths of full).
// @ref __stricmp=00781f20
// @ref ___allmul=007820c0
// @ref ___alldiv=007824d0
#include "shared/audio_event.hpp"

extern "C" int __cdecl _stricmp(char const *left, char const *right);

void __fastcall Audio_Event_Play_Named(char const *name, int volume)
{
    if (Audio_Events_Ready != 0) {
        AudioEventType *type = (AudioEventType *)Audio_List_First(&Audio_Event_Type_List);
        if (type != 0) {
            while (type != 0 && _stricmp(name, type->Name) != 0) {
                type = (AudioEventType *)Audio_List_Next(type);
            }
            AudioEvent *event;
            if (type != 0 && (event = Audio_Event_Create(type)) != 0) {
                int level = (int)((__int64)volume * 0x4000 / 0x100);
                if (level > 0x4000u) {
                    level = 0x4000;
                } else if (level < 0) {
                    level = 0;
                }
                event->Levels.Volume.Set((event->Type->VolumeLevel.Current >> 16) * level >> 14);
                event->Levels.Volume.Update();
            }
        }
    }
}
