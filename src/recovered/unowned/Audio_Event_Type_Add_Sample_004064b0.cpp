// int __fastcall Audio_Event_Type_Add_Sample(AudioEventType *type, char const *name) -- 0x004064B0
// Purpose: adds the bag entry called name (leading '$' and '#' skipped) to the
// sample list of an event type. A missing sample is reported and makes the
// type unusable. Returns 0 only when the list is full.
// @ref ?Audio_Event_Bag@@3PAUAudioBag@@A=00830fac
#include "shared/audio_event.hpp"

int __fastcall Audio_Event_Type_Add_Sample(AudioEventType *type, char const *name)
{
    if (type->SampleCount == 0x20) {
        return 0;
    }
    if (Audio_Events_Ready != 0 && Audio_Event_Bag != 0) {
        while (*name == '$' || *name == '#') {
            name++;
        }
        int index = Audio_Bag_Find(Audio_Event_Bag, name);
        if (index != -1) {
            type->Samples[type->SampleCount] = index;
            type->SampleCount++;
            return 1;
        }
        Debug_Printf("Missing sample %s\n", name);
        type->unknown_0c = 0;
    }
    return 1;
}
