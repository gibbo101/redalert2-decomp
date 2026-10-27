// bool SidebarClass::Scroll(bool up, int column) (0x0067CDD0)
// Scrolls a strip (the active one for -1) by a row and redraws.
#include "shared/sidebar.hpp"
// @ref ?unknown_int_a40d34@@3HA=00a40d34
// @ref ?Scroll@StripClass@SidebarClass@@QAE_N_NH@Z=0067ee60
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_int_83962c@@3HA=0083962c
// @ref ?unknown_int_839624@@3HA=00839624
// @ref ?unknown_abcd64@@3HA=00abcd64

bool SidebarClass::Scroll(bool up, int column)
{
    if (unknown_int_a40d34) {
        return false;
    }
    if (column == -1) {
        column = unknown_4ed8;
    }
    if (Column[column].Scroll(up, 1)) {
        Flag_To_Redraw(false);
        return true;
    }
    return false;
}
