// void ObjectClass::unknown_slot109(int height) (0x005D4860)
#include "shared/object_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280

void ObjectClass::unknown_slot109(int height)
{
    if (unknown_79) {
        height += unknown_geometry_j;
    }
    if (unknown_74) {
        unknown_slot71(0);
        CoordStruct coord = Coord;
        Coord.Z = Map.Unknown_0055A280(coord) + height;
        unknown_slot71(1);
    } else {
        CoordStruct coord = Coord;
        Coord.Z = Map.Unknown_0055A280(coord) + height;
    }
}
