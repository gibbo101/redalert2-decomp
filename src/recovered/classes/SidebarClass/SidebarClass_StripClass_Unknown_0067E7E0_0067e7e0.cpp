// void SidebarClass::StripClass::Unknown_0067E7E0(int id) (0x0067E7E0)
// Numbers the strip and lays out its icon buttons (two per row) at the
// strip's origin.
#include "shared/sidebar.hpp"
#include "shared/sidebar_screen.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?SelectButton@SidebarClass@@2PAVSelectClass@StripClass@1@A=00ab9740
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_int_83962c@@3HA=0083962c
// @ref ?unknown_int_839624@@3HA=00839624
// @ref ?unknown_abcd64@@3HA=00abcd64
// @ref ?unknown_abcd68@@3HA=00abcd68
// @ref ?unknown_abcd6c@@3HA=00abcd6c

void SidebarClass::StripClass::Unknown_0067E7E0(int id)
{
    unknown_34 = id;
    int rows = Map.Unknown_006820A0();
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < 2; column++) {
            int index = row * 2 + column;
            SelectClass &button = SelectButton[unknown_34 * 60 + index];
            button.ID = 202;
            button.X = Map.Column[unknown_34].unknown_1c + unknown_abcd68 * column;
            button.Y = Map.Column[unknown_34].unknown_20 + unknown_abcd6c * row + 1;
            button.Width = 60;
            button.Height = 48;
            button.Strip = this;
            button.Index = index;
        }
    }
}
