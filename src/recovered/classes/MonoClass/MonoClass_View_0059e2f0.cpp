// void MonoClass::View() (0x0059E2F0)
// Shows this window: a window that was not on display is cleared first.
#include "shared/mono_class.hpp"
// @ref ?unknown_mono_enabled_a70f0a@@3_NA=00a70f0a
// @ref ?unknown_mono_viewed_a70f0c@@3PAVMonoClass@@A=00a70f0c
// @ref ?Refresh@MonoClass@@QAEXHHHH@Z=0059ea90

void MonoClass::View()
{
    if (unknown_mono_enabled_a70f0a) {
        if (unknown_mono_viewed_a70f0c != this) {
            unknown_mono_viewed_a70f0c = this;
            Clear();
        }
        Refresh(0, 0, 80, 25);
    }
}
