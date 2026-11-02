// CoordStruct __fastcall Adjacent_Coord_With_Height(CoordStruct const &coord, int facing) -- 0x00491880
// TibSun coord.cpp: the coordinate one cell toward a facing (the AdjacentPoint offsets at
// 0x00851AC0), its height moved by the ground-height difference between the two places.
#include "shared/coord.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280

CoordStruct __fastcall Adjacent_Coord_With_Height(CoordStruct const &coord, int facing)
{
    CoordStruct newcoord = (coord + unknown_adjacent_offsets_00851ac0[facing]);
    newcoord.Z += Map.Unknown_0055A280(newcoord) - Map.Unknown_0055A280(coord);
    return newcoord;
}
