// void Voc_Static_Update() (0x00714330): moves every unpaused static sound's
// event to its coordinate (0x007141B0) and drops the sounds whose event ended,
// unless their type loops forever (hypothesis).
#include "shared/voc_static.hpp"
// @ref ?unknown_voc_static_list_ad07d0@@3UAudioListNode@@A=00ad07d0
// @ref ?unknown_voc_static_pool_ad0844@@3PAUAudioPool@@A=00ad0844
// @ref ?Audio_Event_Handle_Event@@YIPAUAudioEvent@@PAUAudioEventHandle@@@Z=00406140
// @ref ?Audio_Event_Handle_Type@@YIPAUAudioEventType@@PAUAudioEventHandle@@@Z=00406180
// @ref ?Audio_Event_Type_Loops_Forever@@YIHPAUAudioEventType@@@Z=00406660
// @ref ?Voc_Update_At@@YIPAUAudioEvent@@ABUCoordStruct@@PAUAudioEventHandle@@@Z=007141b0

void Voc_Static_Update()
{
    VocStaticSound *sound = (VocStaticSound *)Audio_List_First(&unknown_voc_static_list_ad07d0);
    while (sound != 0) {
        VocStaticSound *next = (VocStaticSound *)Audio_List_Next(sound);
        if (sound->PauseCount == 0) {
            Voc_Update_At(sound->Coord, &sound->Handle);
        }
        if (Audio_Event_Handle_Event(&sound->Handle) == 0) {
            AudioEventType *type = Audio_Event_Handle_Type(&sound->Handle);
            if (type == 0 || !Audio_Event_Type_Loops_Forever(type)) {
                Audio_List_Remove(sound);
                Audio_Pool_Free(unknown_voc_static_pool_ad0844, sound);
                Audio_Static_Sound_Count--;
            }
        }
        sound = next;
    }
}
