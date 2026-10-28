// void Voc_Static_Pause() (0x007144B0): pauses every static sound.
#include "shared/voc_static.hpp"
// @ref ?unknown_voc_static_list_ad07d0@@3UAudioListNode@@A=00ad07d0

void Voc_Static_Pause()
{
    for (VocStaticSound *sound = (VocStaticSound *)Audio_List_First(&unknown_voc_static_list_ad07d0); sound != 0;
         sound = (VocStaticSound *)Audio_List_Next(sound)) {
        sound->Pause();
    }
}
