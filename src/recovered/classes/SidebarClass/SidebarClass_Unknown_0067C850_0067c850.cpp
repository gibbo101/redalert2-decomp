// void SidebarClass::Unknown_0067C850() (0x0067C850)
// Enables the scroll buttons while the active strip has more icons than fit.
#include "shared/sidebar.hpp"
// @ref ?Is_Enabled@GadgetClass@@QAE_NXZ=004cf160
// @ref ?Enable@GadgetClass@@UAEXXZ=004cf140
// @ref ?Disable@GadgetClass@@UAEXXZ=004cf150
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_int_83962c@@3HA=0083962c
// @ref ?unknown_int_839624@@3HA=00839624
// @ref ?unknown_abcd64@@3HA=00abcd64

void SidebarClass::Unknown_0067C850()
{
    if (Column[unknown_4ed8].BuildableCount > Unknown_006820A0() * 2) {
        if (!unknown_button_abcbe8.Is_Enabled()) {
            unknown_button_abcbe8.Enable();
        }
        if (!unknown_button_abccc0.Is_Enabled()) {
            unknown_button_abccc0.Enable();
        }
    } else {
        if (unknown_button_abcbe8.Is_Enabled()) {
            unknown_button_abcbe8.Disable();
        }
        if (unknown_button_abccc0.Is_Enabled()) {
            unknown_button_abccc0.Disable();
        }
    }
}
