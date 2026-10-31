// void Mono_Clear_All_Pages() (0x0059DAD0)
#include "shared/mono_window.hpp"
// @ref ?unknown_mono_pages_a70e40@@3PAPAVMonoClass@@A=00a70e40
// @ref ?Refresh@MonoClass@@QAEXHHHH@Z=0059ea90

void Mono_Clear_All_Pages()
{
    for (int i = 0; i < 8; i++) {
        unknown_mono_pages_a70e40[i]->Clear();
    }
}
