// void Voc_Static_Resume() (0x007144F0): resumes every static sound.
#include "shared/voc_static.hpp"
// @ref ?unknown_voc_static_list_ad07d0@@3UAudioListNode@@A=00ad07d0

void Voc_Static_Resume()
{
    for (VocStaticSound *sound = (VocStaticSound *)Audio_List_First(&unknown_voc_static_list_ad07d0); sound != 0;
         sound = (VocStaticSound *)Audio_List_Next(sound)) {
        sound->Resume();
    }
}
