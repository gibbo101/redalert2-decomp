// Unknown84E8D0::Unknown_0042E740 (0x0042E740): selects the beacon within 128 of the point
// (unselecting everything else first); 0x0042E860 is expanded.
#include "shared/beacon.hpp"
#include "shared/main_loop.hpp"

bool Unknown84E8D0::Unknown_0042E740(int x, int y, int z)
{
    UnknownBeacon *beacon = Unknown_0042E860(CoordStruct(x, y, z));
    if (beacon) {
        Unknown_00482BC0();
        beacon->unknown_flags |= 2;
        return true;
    }
    return false;
}
