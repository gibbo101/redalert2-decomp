// void SidebarClass::StripClass::Unknown_0067E8F0() (0x0067E8F0)
// Adds the strip's visible icon buttons to the screen's list.
#include "shared/sidebar.hpp"
#include "shared/sidebar_screen.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?SelectButton@SidebarClass@@2PAVSelectClass@StripClass@1@A=00ab9740
// @ref ?Zap@LinkClass@@UAEXXZ=00538ff0
// @ref ?Add_A_Button@GScreenClass@@UAEXAAVGadgetClass@@@Z=004e0ac0
// @ref ?unknown_flag_8373c3@@3_NA=008373c3
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_int_83962c@@3HA=0083962c
// @ref ?unknown_int_839624@@3HA=00839624
// @ref ?unknown_abcd64@@3HA=00abcd64

void SidebarClass::StripClass::Unknown_0067E8F0()
{

    int max = Map.Unknown_006820F0();
    for (int index = 0; index < max; index++) {
        SelectButton[unknown_34 * 60 + index].Zap();
        Map.Add_A_Button(SelectButton[unknown_34 * 60 + index]);
    }
    unknown_flag_8373c3 = true;
}
