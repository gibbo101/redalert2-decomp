// UnknownBeacon::Unknown_0042DD60 (0x0042DD60): takes a position other than the default one and a
// house below 8 (then marks it placed). Out of line here; 0x0042E370 expands it.
// The position is stored through a fresh CoordStruct built from the parameter's members: that temporary
// gives the original's order (default X loaded before the Y parameter, Z in esi, Y in edx); storing the
// parameter itself swaps the Y and Z registers.
#include "shared/beacon.hpp"
#include "shared/unknown_geometry.hpp"

void UnknownBeacon::Unknown_0042DD60(CoordStruct coord, int house)
{
    if (coord != unknown_geometry_l) {
        unknown_coord = CoordStruct(coord.X, coord.Y, coord.Z);
    }
    if (house < 8) {
        unknown_house = house;
        unknown_flags |= 1;
    }
}
