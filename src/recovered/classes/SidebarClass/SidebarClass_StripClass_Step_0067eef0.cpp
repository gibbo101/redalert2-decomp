// bool SidebarClass::StripClass::Step(bool up) (0x0067EEF0)
// Requests a one-row scroll.
#include "shared/sidebar.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_int_83962c@@3HA=0083962c
// @ref ?unknown_int_839624@@3HA=00839624
// @ref ?unknown_abcd64@@3HA=00abcd64

bool SidebarClass::StripClass::Step(bool up)
{
    return Scroll(up, 1);
}
