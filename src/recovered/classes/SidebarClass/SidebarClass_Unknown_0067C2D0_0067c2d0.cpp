// void SidebarClass::Unknown_0067C2D0(int column) (0x0067C2D0)
// Redraws a strip when it is the active one.
#include "shared/sidebar.hpp"
#include "shared/sidebar_screen.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

void SidebarClass::Unknown_0067C2D0(int column)
{
    if (column == unknown_4ed8) {
        unknown_4ee2 = true;
        Column[column].unknown_38 = true;
        Map.Flag_To_Redraw(false);
    }
}
