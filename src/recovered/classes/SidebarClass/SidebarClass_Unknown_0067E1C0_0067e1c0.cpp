// void SidebarClass::Unknown_0067E1C0() (0x0067E1C0)
// Runs every strip; redraws when the active one changed.
#include "shared/sidebar.hpp"
// @ref ?Unknown_006802D0@StripClass@SidebarClass@@QAE_NXZ=006802d0

void SidebarClass::Unknown_0067E1C0()
{
    bool redraw = false;
    for (int index = 0; index < 4; index++) {
        if (Column[index].Unknown_006802D0() && index == unknown_4ed8) {
            Column[index].unknown_38 = true;
            redraw = true;
        }
    }
    if (redraw) {
        unknown_4ee2 = true;
        Flag_To_Redraw(false);
    }
}
