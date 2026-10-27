// void SidebarClass::Unknown_0067BA60() (0x0067BA60)
// Places the sidebar right of the tactical area (when shown) and its
// control columns.
#include "shared/sidebar.hpp"
// @ref ?unknown_flag_a40b30@@3_NA=00a40b30
// @ref ?unknown_int_839620@@3HA=00839620
// @ref ?unknown_int_839630@@3HA=00839630
// @ref ?unknown_int_839638@@3HA=00839638
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_abcd48@@3HA=00abcd48
// @ref ?unknown_abcd54@@3HA=00abcd54
// @ref ?unknown_abcd60@@3HA=00abcd60
// @ref ?unknown_abcd74@@3HA=00abcd74

void SidebarClass::Unknown_0067BA60()
{
    int x = unknown_flag_a40b30 ? unknown_int_839630 + unknown_int_839638 : 0;
    unknown_int_839620 = x;
    unknown_abcd60 = x + 22;
    if (unknown_id_source_a3d290->unknown_2239) {
        unknown_abcd48 = x + 20;
        unknown_abcd54 = x + 26;
        unknown_abcd74 = x + 39;
    } else {
        unknown_abcd48 = x + 33;
        unknown_abcd54 = x + 20;
        unknown_abcd74 = x + 39;
    }
}
