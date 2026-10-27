// int SidebarClass::Unknown_006820A0() (0x006820A0)
// The rows of icons that fit in a strip: the sidebar height below the top
// pieces, less the bottom piece (26 lines when the scenario flag at +0x2239
// is set, else 18) and 7, in rows of 50.
#include "shared/sidebar.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_int_83962c@@3HA=0083962c
// @ref ?unknown_int_839624@@3HA=00839624
// @ref ?unknown_abcd64@@3HA=00abcd64

int SidebarClass::Unknown_006820A0()
{
    int extra;
    if (unknown_id_source_a3d290->unknown_2239) {
        extra = 26;
    } else {
        extra = 18;
    }
    return (unknown_int_839624 + unknown_int_83962c - unknown_abcd64 - extra - 7) / 50;
}
