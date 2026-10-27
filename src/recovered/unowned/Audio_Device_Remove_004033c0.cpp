// void __fastcall Audio_Device_Remove(AudioDevice *device) -- 0x004033C0
// Purpose: unlinks the device from the system's device list (the system
// marked busy meanwhile) and destroys it as 0x00402EF0 does.
// @ref ?Audio_System_Instance@@3PAUAudioSystem@@A=007cc968
#include "shared/audio.hpp"

void __cdecl operator delete(void *block);

void __fastcall Audio_Device_Remove(AudioDevice *device)
{
    Audio_System_Instance->Busy++;
    Audio_List_Remove(device);
    if (--Audio_System_Instance->Busy < 0) {
        Audio_System_Instance->Busy = 0;
    }
    Audio_Device_Destroy(device);
}
