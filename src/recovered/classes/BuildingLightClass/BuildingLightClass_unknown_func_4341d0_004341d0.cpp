#include "shared/building_light.hpp"
#include "shared/rules.hpp"
// @ref ?unknown_facing_radians_79b620@@3NB=0079b620
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0
// @ref ?unknown_sin_4ba480@@YANN@Z=004ba480
// @ref ?unknown_cos_4ba4d0@@YANN@Z=004ba4d0
// @ref ?unknown_slot103@ObjectClass@@UAEXABUCoordStruct@@@Z=005d51c0

// The point DISTANCE leptons from COORD along FACING (in the ground plane;
// Z is kept). Expanded twice by 0x004341D0 and, through it, the constructor.
static inline CoordStruct Coord_Along_Facing(UnknownFacingDir facing, int distance, CoordStruct coord)
{
    double angle = ((short)facing.Raw - 0x3fff) * unknown_facing_radians_79b620;
    double y = coord.Y;
    return CoordStruct((int)(unknown_cos_4ba4d0(angle) * distance + coord.X), (int)(y - unknown_sin_4ba480(angle) * distance), coord.Z);
}

// Places the light's two points in front of and behind OBJECT (Rules
// +0x6B4 ahead, +0x6B0 behind) and moves the light to the front one.
void BuildingLightClass::unknown_func_4341d0(TechnoClass *object)
{
    CoordStruct near_point = Coord_Along_Facing(object->unknown_2e0.Current(), Rules->unknown_6b4, object->Coord);
    unknown_ac = near_point;
    unknown_a0 = Coord_Along_Facing(object->unknown_2e0.Current(), -Rules->unknown_6b0, object->Coord);
    unknown_slot103(near_point);
}
