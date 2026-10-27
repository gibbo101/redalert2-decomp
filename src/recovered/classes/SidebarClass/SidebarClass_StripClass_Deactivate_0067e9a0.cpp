// void SidebarClass::StripClass::Deactivate() (0x0067E9A0)
// Removes the strip's visible icon buttons from the screen's list.
#include "shared/sidebar.hpp"
#include "shared/sidebar_screen.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?SelectButton@SidebarClass@@2PAVSelectClass@StripClass@1@A=00ab9740

void SidebarClass::StripClass::Deactivate()
{
    int max = Map.Unknown_006820F0();
    for (int index = 0; index < max; index++) {
        Map.Remove_A_Button(SelectButton[unknown_34 * 60 + index]);
    }
}
