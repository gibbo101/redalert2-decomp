// bool SidebarClass::StripClass::Page(bool up) (0x0067EF70)
// Requests a one-page scroll.
#include "shared/sidebar.hpp"
#include "shared/sidebar_screen.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_int_83962c@@3HA=0083962c
// @ref ?unknown_int_839624@@3HA=00839624
// @ref ?unknown_abcd64@@3HA=00abcd64

bool SidebarClass::StripClass::Page(bool up)
{
    int amount = Map.Unknown_006820A0();
    return Scroll(up, amount);
}
