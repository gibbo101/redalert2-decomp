// bool SidebarClass::Scroll_Page(bool up, int column) (0x0067CE90)
// Scrolls a strip (the active one for -1) by a page and redraws.
#include "shared/sidebar.hpp"
// @ref ?Scroll@StripClass@SidebarClass@@QAE_N_NH@Z=0067ee60
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_int_83962c@@3HA=0083962c
// @ref ?unknown_int_839624@@3HA=00839624
// @ref ?unknown_abcd64@@3HA=00abcd64

bool SidebarClass::Scroll_Page(bool up, int column)
{
    if (column == -1) {
        column = unknown_4ed8;
    }
    StripClass &strip = Column[column];
    int amount = Unknown_006820A0();
    if (strip.Scroll(up, amount)) {
        Flag_To_Redraw(false);
        return true;
    }
    return false;
}
