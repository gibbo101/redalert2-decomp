// void ObjectClass::unknown_slot59(CoordStruct const &coord) (0x005D49E0, slot 59)
// Clears the Monolith occupation bit (0x40) of the cell at coord: the bridge level's (+0x128)
// when coord is at or above the bridge height over a bridge cell, else the
// ground's (+0x124).
#include "shared/object_type.hpp"
#include "shared/techno.hpp"
#include "shared/techno_map.hpp"
// @ref _unknown_geometry_j=00a72f30

void ObjectClass::unknown_slot59(CoordStruct const &coord)
{
    if (Map.Unknown_0055A280(coord) + unknown_geometry_j <= coord.Z && (Map_Cell(coord)->Flags & 0x100)) {
        Map_Cell(coord)->unknown_128.Occupy.Monolith = false;
    } else {
        Map_Cell(coord)->unknown_124.Occupy.Monolith = false;
    }
}
