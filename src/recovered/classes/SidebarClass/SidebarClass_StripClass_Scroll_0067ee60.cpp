// bool SidebarClass::StripClass::Scroll(bool up, int amount) (0x0067EE60)
// Requests a scroll of the strip unless it is already at that end.
#include "shared/sidebar.hpp"
#include "shared/sidebar_screen.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_int_83962c@@3HA=0083962c
// @ref ?unknown_int_839624@@3HA=00839624
// @ref ?unknown_abcd64@@3HA=00abcd64

bool SidebarClass::StripClass::Scroll(bool up, int amount)
{
    if (up) {
        if (!unknown_40) {
            return false;
        }
        unknown_44 -= amount;
        return true;
    }
    if ((unknown_40 + Map.Unknown_006820A0()) * 2 >= BuildableCount) {
        return false;
    }
    unknown_44 += amount;
    return true;
}
