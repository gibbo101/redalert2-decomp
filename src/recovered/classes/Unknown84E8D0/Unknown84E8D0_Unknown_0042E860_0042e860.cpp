// Unknown84E8D0::Unknown_0042E860 (0x0042E860): the beacon within 128 of the point, else none.
#include "shared/beacon.hpp"

UnknownBeacon *Unknown84E8D0::Unknown_0042E860(CoordStruct coord)
{
    if (unknown_60) {
        for (int house = 0; house < 8; house++) {
            for (int slot = 0; slot < 3; slot++) {
                if (unknown_00[house][slot] && Beacon_Distance(coord, unknown_00[house][slot]->unknown_coord) < 128) {
                    return unknown_00[house][slot];
                }
            }
        }
    }
    return 0;
}
