// void SetUnitTabCommandClass::Execute(int key) const -- 0x0051B240
// Switches the sidebar to tab 3 when that column has anything to build
// (StripClass at 0x0083654C, Column[3] of the screen at 0x008324E0).
#include "shared/command.hpp"
#include "shared/sidebar_screen.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_00681730@StripClass@SidebarClass@@QAE_NXZ=00681730
// @ref ?Select_Tab@SidebarClass@@QAEXH@Z=0067d990

void SetUnitTabCommandClass::Execute(int key) const
{
    if (Map.Column[3].Unknown_00681730()) {
        Map.Select_Tab(3);
    }
}
