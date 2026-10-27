// int PowerClass::Unknown_0061C5F0() (0x0061C5F0, static)
// The bar segments left unlit for the player's buildings: the share of the
// bar the output (less the drain) leaves, 400 / (power + 400) of the
// segments, clamped to the bar.
#include "shared/power.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_int_abcd70@@3HA=00abcd70
// @ref __real@8@4007c800000000000000=007a5e08
// @ref __ftol=0077f110

int PowerClass::Unknown_0061C5F0()
{
    HouseClass *house = unknown_player_a35db4;
    int segments = Unknown_0061C6E0();
    int drain = 0;
    int output = 0;
    for (int index = 0; index < house->Buildings.Count(); index++) {
        UnknownBuilding *building = house->Buildings[index];
        drain += building->Type->PowerDrain_c6c;
        output += building->Type->unknown_c68;
    }
    int total = output + drain;
    double bar = 400.0 / ((double)total + 400.0);
    int lit = (int)(bar * segments);
    lit = (lit > 0) ? lit : 0;
    if (lit >= segments - 1) {
        lit = segments - 1;
    }
    return segments - lit;
}
