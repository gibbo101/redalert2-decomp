// int __fastcall Audio_Events_Init(AudioDevice *device, AudioBag *bag) -- 0x00403EB0
// Purpose: starts the event system: empties the event lists, resets the
// shared levels and, when there is a bag, builds the sample bank and the event
// pool. Returns 1 when everything needed exists.
#include "shared/audio_event.hpp"

int __fastcall Audio_Events_Init(AudioDevice *device, AudioBag *bag)
{
    Audio_List_Init(&Audio_Event_List);
    Audio_List_Init(&Audio_Event_Type_List);
    Audio_Event_Bag = bag;
    Audio_Event_Device = device;
    Audio_Event_Levels.Init();
    Audio_Event_Maximum = 0;
    Audio_Event_Count = 0;
    Audio_Events_Ready = 1;
    Audio_Enabled = 1;
    if (Audio_Event_Bag != 0) {
        Audio_Event_Bank = Audio_Bank_Create(Audio_Event_Bag, 0x100000, 200, 0x2000);
        Audio_Event_Pool = Audio_Pool_Create(100, 0x280);
        Debug_Printf("event mempool size = %d\n", 64000);
    }
    if (Audio_Event_Bank != 0 && Audio_Event_Bag != 0 && Audio_Event_Device != 0 && Audio_Event_Pool != 0) {
        Audio_Events_Open = 1;
        return 1;
    }
    return 0;
}
