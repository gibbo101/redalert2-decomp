// AudioEventType *__fastcall Audio_Event_Type_Find(char const *name) -- 0x004063C0
// Purpose: finds the event type with this name, or makes a new one with the
// default settings and adds it to the type list.
// @ref __stricmp=00781f20
// @ref _strncpy=007823d0
#include "shared/crt_memory.hpp"
#include "shared/audio_event.hpp"

extern "C" int __cdecl _stricmp(char const *left, char const *right);
extern "C" char *__cdecl strncpy(char *destination, char const *source, unsigned int count);
void *__cdecl operator new(unsigned int size);

AudioEventType *__fastcall Audio_Event_Type_Find(char const *name)
{
    AudioEventType *type;

    if (Audio_Events_Ready == 0) {
        return 0;
    }
    type = (AudioEventType *)Audio_List_First(&Audio_Event_Type_List);
    for (;;) {
        if (type == 0) {
        make:
            type = (AudioEventType *)operator new(sizeof(AudioEventType));
            memset(type, 0, sizeof(AudioEventType));
            memset(type, 0, sizeof(AudioEventType));
            Audio_List_Init_Node(type);
            type->unknown_0c = 1;
            type->Flags = 0;
            type->unknown_14 = 0x20;
            type->unknown_48 = 3;
            type->unknown_40 = 2;
            type->unknown_50 = 10;
            type->unknown_54 = 0.2f;
            type->VolumeLevel.Init(0x4000);
            strncpy(type->Name, name, sizeof(type->Name) - 1);
            type->Name[sizeof(type->Name) - 1] = 0;
            Audio_List_Add_Tail(&Audio_Event_Type_List, type);
            return type;
        }
        if (_stricmp(name, type->Name) == 0) {
            if (type != 0) {
                return type;
            }
            goto make;
        }
        type = (AudioEventType *)Audio_List_Next(type);
    }
}
