// int SidebarClass::StripClass::Unknown_0067F7C0(int index) (0x0067F7C0)
// An icon's progress: its factory's completion, or (for type 1) the mean
// with the stage value when that is ahead.
#include "shared/sidebar.hpp"
// @ref ?Unknown_004B98F0@UnknownFactory@@QAEHXZ=004b98f0

int SidebarClass::StripClass::Unknown_0067F7C0(int index)
{
    int progress = 0;
    if (Buildables[index].Factory) {
        progress = Buildables[index].Factory->Unknown_004B98F0();
    }
    if (Buildables[index].unknown_10 == 1 && Buildables[index].Stage.Value > progress) {
        progress = (progress + Buildables[index].Stage.Value) / 2;
    }
    return progress;
}
