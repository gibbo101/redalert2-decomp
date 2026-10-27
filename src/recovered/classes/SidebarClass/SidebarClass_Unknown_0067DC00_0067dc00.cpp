#include "shared/sidebar_screen.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
void SidebarClass::Unknown_0067DC00(int index)
{
    int delay = 10 - Frame % 10;
    unknown_buttons_ab9508[index].Unknown_006752D0(10, delay, (Frame + delay) / 10 % 2 == 0);
    Map.unknown_4ee3 = true;
    Map.Flag_To_Redraw(false);
}
