// void Unknown_00714410() (0x00714410): stops and drops every static sound
// (Do_Restart and Clear_Scenario call it; hypothesis).
#include "shared/voc_static.hpp"
#include "shared/vox_class.hpp"
// @ref ?unknown_voc_static_list_ad07d0@@3UAudioListNode@@A=00ad07d0
// @ref ?unknown_voc_static_pool_ad0844@@3PAUAudioPool@@A=00ad0844

void Unknown_00714410()
{
    VocStaticSound *sound = (VocStaticSound *)Audio_List_First(&unknown_voc_static_list_ad07d0);
    while (sound != 0) {
        VocStaticSound *next = (VocStaticSound *)Audio_List_Next(sound);
        Audio_Event_Handle_Stop(&sound->Handle);
        Audio_List_Remove(sound);
        Audio_Pool_Free(unknown_voc_static_pool_ad0844, sound);
        Audio_Static_Sound_Count--;
        sound = next;
    }
}
