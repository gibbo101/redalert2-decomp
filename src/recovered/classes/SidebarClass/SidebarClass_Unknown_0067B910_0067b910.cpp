// void SidebarClass::Unknown_0067B910() (0x0067B910)
// Lays out the sidebar from the screen size: its width and height, the
// strip and button positions (two variants by the 0x00A3D290 option), the
// icon count that fits (a multiple of 50 pixels of height) and the
// background rectangle.
#include "shared/sidebar.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_int_7add80@@3HA=007add80
// @ref ?unknown_int_7add84@@3HA=007add84
// @ref ?unknown_int_83963c@@3HA=0083963c
// @ref ?unknown_int_839634@@3HA=00839634
// @ref ?unknown_int_839628@@3HA=00839628
// @ref ?unknown_int_839624@@3HA=00839624
// @ref ?unknown_int_83962c@@3HA=0083962c
// @ref ?unknown_abcd4c@@3HA=00abcd4c
// @ref ?unknown_abcd50@@3HA=00abcd50
// @ref ?unknown_abcd58@@3HA=00abcd58
// @ref ?unknown_abcd5c@@3HA=00abcd5c
// @ref ?unknown_abcd64@@3HA=00abcd64
// @ref ?unknown_abcd68@@3HA=00abcd68
// @ref ?unknown_abcd6c@@3HA=00abcd6c
// @ref ?unknown_int_abcd70@@3HA=00abcd70
// @ref ?unknown_abcd78@@3HA=00abcd78
// @ref ?unknown_abcd7c@@3HA=00abcd7c
// @ref ?unknown_abcd80@@3HA=00abcd80

void SidebarClass::Unknown_0067B910()
{
    unknown_int_839628 = unknown_int_7add80;
    unknown_int_839624 = 0x9E;
    unknown_int_83962c = unknown_int_839634 + unknown_int_83963c + unknown_int_7add84 - 0x9E;
    if (unknown_id_source_a3d290->unknown_2239) {
        unknown_abcd4c = 0xA6;
        unknown_abcd50 = 0x40;
        unknown_abcd58 = 0xC5;
        unknown_abcd5c = 0x1D;
        unknown_abcd64 = 0xE3;
        unknown_abcd68 = 0x3F;
    } else {
        unknown_abcd4c = 0xA5;
        unknown_abcd50 = 0x34;
        unknown_abcd58 = 0xC5;
        unknown_abcd5c = 0x20;
        unknown_abcd64 = 0xE3;
        unknown_abcd68 = 0x40;
    }
    unknown_abcd6c = 0x32;
    int extra;
    if (unknown_id_source_a3d290->unknown_2239) {
        extra = 26;
    } else {
        extra = 18;
    }
    unknown_int_abcd70 = (unknown_int_83962c - extra - 0x4C) / 50 * 50;
    if (unknown_id_source_a3d290->unknown_2239) {
        unknown_abcd78 = unknown_int_abcd70 + 0xEA;
        unknown_abcd7c = 0x2E;
        unknown_abcd80 = 0x32;
    } else {
        unknown_abcd78 = unknown_int_abcd70 + 0xEA;
        unknown_abcd7c = 0x2D;
        unknown_abcd80 = 0x32;
    }
}
