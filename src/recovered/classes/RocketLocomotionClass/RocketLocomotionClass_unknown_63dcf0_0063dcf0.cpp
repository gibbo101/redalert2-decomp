// bool RocketLocomotionClass::unknown_63dcf0(RocketStruct const *rocket) (0x0063DCF0)
// Detonates (0x0063E7D0) when the rocket's nose (BodyLength ahead) is down
// to the destination height, or to the bridge-deck height above it when
// the rocket is over a bridge cell at the destination height. True when it
// detonated.
#include "shared/rocket_locomotion.hpp"
#include "shared/rules.hpp"
#include "shared/cell_class.hpp"
#include "shared/unknown_geometry.hpp"

bool RocketLocomotionClass::unknown_63dcf0(RocketStruct const *rocket)
{
    int z = unknown_63dbe0(rocket->BodyLength).Z;
    if (z <= unknown_18.Z) {
        unknown_63e7d0();
        return true;
    }
    CellClass *cell = static_cast<CellClass *>(LinkedTo->unknown_slot105());
    if (cell != 0 && (cell->unknown_140 & 0x100) && cell->Center_Coord().Z == unknown_18.Z && z <= unknown_18.Z + unknown_geometry_j) {
        unknown_63e7d0();
        return true;
    }
    return false;
}
