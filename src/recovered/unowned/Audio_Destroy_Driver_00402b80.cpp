// void __fastcall Audio_Destroy_Driver(AudioDriver *driver) -- 0x00402B80
// Purpose: unlinks the driver instance, releases it through its
// descriptor, clears the descriptor's in-use flag, deletes it and clears
// 0x00830B48.
// @ref ?Audio_List_Remove@@YIXPAUAudioListNode@@@Z=00407380
// @ref ?Audio_unknown_830b48@@3HA=00830b48
#include "shared/audio.hpp"

void __cdecl operator delete(void *block);

void __fastcall Audio_Destroy_Driver(AudioDriver *driver)
{
    Audio_List_Remove(driver);
    driver->Info->Release(driver);
    driver->Info->Flags &= ~1;
    operator delete(driver);
    Audio_unknown_830b48 = 0;
}
