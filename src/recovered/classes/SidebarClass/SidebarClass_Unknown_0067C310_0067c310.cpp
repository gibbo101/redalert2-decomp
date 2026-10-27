// void SidebarClass::Unknown_0067C310(int column) (0x0067C310)
// Redraws a strip when it is the active one, and again within two frames.
#include "shared/sidebar.hpp"
#include "shared/sidebar_screen.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

void SidebarClass::Unknown_0067C310(int column)
{
    if (column == unknown_4ed8) {
        unknown_4ee2 = true;
        Column[unknown_4ed8].unknown_38 = true;
        Map.Flag_To_Redraw(false);
        if (unknown_4edc <= Frame) {
            unknown_4edc = Frame + 2;
        }
    }
}
