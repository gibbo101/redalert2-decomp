// void SidebarClass::StripClass::Unknown_0067E770() (0x0067E770)
// Clears the strip's state (Init_Clear): no scroll or redraw flags, no
// first icon, no buildables, and every buildable entry reset.
#include "shared/sidebar.hpp"

void SidebarClass::StripClass::Unknown_0067E770()
{
    unknown_3a = false;
    unknown_3b = false;
    unknown_39 = false;
    unknown_3c = -1;
    unknown_40 = 0;
    unknown_48 = 0;
    BuildableCount = 0;
    for (int index = 0; index < 75; index++) {
        Buildables[index].unknown_00 = 0;
        Buildables[index].unknown_04 = 0;
        Buildables[index].unknown_08 = 0;
        Buildables[index].Factory = 0;
        Buildables[index].unknown_10 = 0;
        Buildables[index].Stage.Set_Rate(0);
        Buildables[index].Stage.Value = 0;
        Buildables[index].unknown_2c = 0;
    }
}
