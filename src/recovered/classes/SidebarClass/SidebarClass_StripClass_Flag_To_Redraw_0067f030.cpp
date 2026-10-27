// void SidebarClass::StripClass::Flag_To_Redraw() (0x0067F030)
#include "shared/sidebar.hpp"
#include "shared/sidebar_screen.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

void SidebarClass::StripClass::Flag_To_Redraw()
{
    unknown_38 = true;
    Map.Flag_To_Redraw(false);
}
