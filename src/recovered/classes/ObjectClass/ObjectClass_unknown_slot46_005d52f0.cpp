// bool ObjectClass::unknown_slot46(int arg1) (0x005D52F0, slot 46)
// Starts from +0x79 (on a bridge). Compares the ground height under slot 19's
// coordinate for arg1 with the ground height under the object: off a bridge,
// a drop of more than three height levels (unknown_geometry_g) onto a bridge
// cell answers true; on a bridge, a rise of more than three levels answers
// false. arg1 is passed to slot 19 as its TechnoClass argument.
#include "shared/object_type.hpp"
#include "shared/techno.hpp"
#include "shared/techno_map.hpp"
// @ref _unknown_geometry_g=00a72f40

bool ObjectClass::unknown_slot46(int arg1)
{
    bool result = unknown_79;
    CoordStruct coord = unknown_slot19((TechnoClass *)arg1);
    int there = Map.Unknown_0055A280(coord);
    int ground = Map.Unknown_0055A280(CoordStruct(Coord));
    if (!unknown_79 && ground - there > unknown_geometry_g * 3 && (Map_Cell(coord)->Flags & 0x100)) {
        return true;
    }
    if (unknown_79 && there - ground > unknown_geometry_g * 3) {
        return false;
    }
    return result;
}
