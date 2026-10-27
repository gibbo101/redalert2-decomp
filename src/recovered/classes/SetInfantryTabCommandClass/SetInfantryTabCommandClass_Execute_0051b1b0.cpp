// void SetInfantryTabCommandClass::Execute(int key) const -- 0x0051B1B0
// Switches the sidebar to tab 2 when that column has anything to build
// (StripClass at 0x008356E8, Column[2] of the screen at 0x008324E0).
#include "shared/command.hpp"
#include "shared/sidebar_screen.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_00681730@StripClass@SidebarClass@@QAE_NXZ=00681730
// @ref ?Select_Tab@SidebarClass@@QAEXH@Z=0067d990

void SetInfantryTabCommandClass::Execute(int key) const
{
    if (Map.Column[2].Unknown_00681730()) {
        Map.Select_Tab(2);
    }
}
