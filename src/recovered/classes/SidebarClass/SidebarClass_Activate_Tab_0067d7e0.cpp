// void SidebarClass::Activate_Tab(int index) (0x0067D7E0)
// Makes a tab current: presses its button, shows its strip and refreshes
// the scroll buttons.
#include "shared/sidebar.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Turn_On@ToggleClass@@QAEXXZ=006eb160
// @ref ?Activate@StripClass@SidebarClass@@QAEXXZ=0067f680
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_int_83962c@@3HA=0083962c
// @ref ?unknown_int_839624@@3HA=00839624
// @ref ?unknown_abcd64@@3HA=00abcd64

void SidebarClass::Activate_Tab(int index)
{
    unknown_4ed8 = index;
    unknown_buttons_ab9508[index].Turn_On();
    Column[unknown_4ed8].Activate();
    Unknown_0067C850();
}
