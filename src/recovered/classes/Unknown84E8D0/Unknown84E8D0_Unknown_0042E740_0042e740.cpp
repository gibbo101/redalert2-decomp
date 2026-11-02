// Unknown84E8D0::Unknown_0042E740 (0x0042E740): selects the beacon within 128 of the point
// (unselecting everything else first); 0x0042E860 is expanded.
#include "shared/beacon.hpp"
#include "shared/main_loop.hpp"

bool Unknown84E8D0::Unknown_0042E740(CoordStruct coord)
{
    UnknownBeacon *beacon = Unknown_0042E860(coord);
    if (beacon) {
        Unknown_00482BC0();
        beacon->unknown_flags |= 2;
        return true;
    }
    return false;
}
