// int Audio_Ready_Driver_Count() -- 0x00402C40
// Purpose: counts the ready drivers: sums their +0x18 flags over the
// system's driver list.
// @ref ?Audio_List_First@@YIPAUAudioListNode@@PAU1@@Z=004072f0
// @ref ?Audio_List_Next@@YIPAUAudioListNode@@PAU1@@Z=00407310
// @ref ?Audio_System_Instance@@3PAUAudioSystem@@A=007cc968
#include "shared/audio.hpp"

int Audio_Ready_Driver_Count()
{
    int total = 0;
    AudioListCursor cursor;
    cursor.First(&Audio_System_Instance->Drivers);
    for (AudioListNode *node = cursor.Node; node != 0; node = cursor.Next()) {
        total += ((AudioDriver *)node)->unknown_ready_18;
    }
    return total;
}
