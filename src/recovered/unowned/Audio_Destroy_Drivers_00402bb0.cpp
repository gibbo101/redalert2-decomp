// void Audio_Destroy_Drivers() -- 0x00402BB0
// Purpose: destroys every driver instance in the system's driver list
// (Audio_Destroy_Driver expanded inline; compiled in one unit with it).
// @ref ?Audio_List_First@@YIPAUAudioListNode@@PAU1@@Z=004072f0
// @ref ?Audio_List_Next@@YIPAUAudioListNode@@PAU1@@Z=00407310
// @ref ?Audio_System_Instance@@3PAUAudioSystem@@A=007cc968
#include "shared/audio.hpp"

void Audio_Destroy_Drivers()
{
    AudioListNode *next = Audio_List_First(&Audio_System_Instance->Drivers);
    for (AudioListNode *node = next; node != 0; node = next) {
        next = Audio_List_Next(next);
        Audio_Destroy_Driver((AudioDriver *)node);
    }
}
