// void SidebarClass::Unknown_0067C100() (0x0067C100)
// Redraws the active strip, and again within two frames.
#include "shared/sidebar.hpp"
#include "shared/sidebar_screen.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

void SidebarClass::Unknown_0067C100()
{
    unknown_4ee2 = true;
    Column[unknown_4ed8].unknown_38 = true;
    Map.Flag_To_Redraw(false);
    if (unknown_4edc <= Frame) {
        unknown_4edc = Frame + 2;
    }
}
