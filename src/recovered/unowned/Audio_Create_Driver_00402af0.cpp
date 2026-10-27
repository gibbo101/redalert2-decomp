// AudioDriver *__fastcall Audio_Create_Driver(AudioDriverInfo *info) -- 0x00402AF0
// Purpose: makes a zero-filled driver instance for the descriptor and
// initializes it through the descriptor. On failure releases it, clears
// the descriptor's in-use flag, deletes it and returns 0; on success marks
// the descriptor in use, links the instance into the system's driver list
// (setting 0x00830B48 when the descriptor asks for it) and returns it.
// @ref ?Audio_List_Add_Tail@@YIXPAUAudioListNode@@0@Z=00407350
// @ref ?Audio_List_Init_Node@@YIXPAUAudioListNode@@@Z=00407200
// @ref ?Audio_System_Instance@@3PAUAudioSystem@@A=007cc968
// @ref ?Audio_unknown_830b48@@3HA=00830b48
#include "shared/crt_memory.hpp"
#include "shared/audio.hpp"

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *block);

AudioDriver *__fastcall Audio_Create_Driver(AudioDriverInfo *info)
{
    AudioDriver *driver = (AudioDriver *)operator new(sizeof(AudioDriver));
    memset(driver, 0, sizeof(AudioDriver));
    Audio_List_Init_Node(driver);
    driver->DeviceCount = 0;
    driver->Info = info;
    if (info->Init(driver) != DS_OK) {
        if (driver != 0) {
            driver->Info->Release(driver);
            driver->Info->Flags &= ~1;
            operator delete(driver);
        }
        driver = 0;
    }
    if (driver == 0) {
        return 0;
    }
    info->Flags |= 1;
    Audio_List_Add_Tail(&Audio_System_Instance->Drivers, driver);
    if (info->unknown_flags_08 & 2) {
        Audio_unknown_830b48 = 1;
    }
    return driver;
}
