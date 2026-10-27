// void SidebarClass::Select_Tab(int index) (0x0067D990)
// Switches to another tab: releases the old tab button and hides its strip,
// then makes the new tab current.
#include "shared/sidebar.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Turn_Off@ToggleClass@@QAEXXZ=006eb170
// @ref ?Turn_On@ToggleClass@@QAEXXZ=006eb160
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_int_83962c@@3HA=0083962c
// @ref ?unknown_int_839624@@3HA=00839624
// @ref ?unknown_abcd64@@3HA=00abcd64

void SidebarClass::Select_Tab(int index)
{
    if (index == unknown_4ed8) {
        return;
    }
    unknown_buttons_ab9508[unknown_4ed8].Turn_Off();
    Column[unknown_4ed8].Unknown_0067F730();
    Activate_Tab(index);
    unknown_4ee3 = true;
}
