// void SidebarClass::Unknown_0067C910(int index) (0x0067C910)
// Enables a tab button (choosing the first tab when no strip has icons and
// the sidebar piece at 0xABCD30 is loaded) and refreshes the scroll buttons
// for the active tab.
#include "shared/sidebar.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_int_83962c@@3HA=0083962c
// @ref ?unknown_int_839624@@3HA=00839624
// @ref ?unknown_abcd64@@3HA=00abcd64
// @ref ?unknown_shapes_abcd20@@3PAPBXA=00abcd20
// @ref ?Is_Enabled@GadgetClass@@QAE_NXZ=004cf160
// @ref ?Enable@GadgetClass@@UAEXXZ=004cf140
// @ref ?Disable@GadgetClass@@UAEXXZ=004cf150

void SidebarClass::Unknown_0067C910(int index)
{
    if (Unknown_00681980() == -1 && unknown_shapes_abcd20[4]) {
        unknown_4ed4 = 1;
        unknown_4ed0 = 0;
    }
    if (!unknown_buttons_ab9508[index].Is_Enabled()) {
        unknown_buttons_ab9508[index].Enable();
    }
    if (index == unknown_4ed8) {
        Unknown_0067C850();
    }
}
