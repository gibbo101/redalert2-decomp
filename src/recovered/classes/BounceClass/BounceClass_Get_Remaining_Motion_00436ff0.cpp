// double BounceClass::Get_Remaining_Motion() const (0x00436FF0; TibSun bounce.cpp): the
// speed plus the height above the ground (or bridge deck) scaled by gravity; small means at rest.
#include "shared/map_view.hpp"
#include "shared/cell_class.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/building_type_class.hpp"

double BounceClass::Get_Remaining_Motion() const
{
    CoordStruct coord((int)unknown_00.Position.X, (int)unknown_00.Position.Y, (int)unknown_00.Position.Z);

    int height = (int)(unknown_00.Position.Z - Map.Unknown_0055A280(coord));
    if ((Map[coord].unknown_140 & 0x100) && height >= unknown_geometry_j) {
        height -= unknown_geometry_j;
    }
    Vector3 const &velocity = *(Vector3 const *)unknown_00.unknown_24;
    TPoint3D<int> point((int)velocity.X, (int)velocity.Y, (int)(height * unknown_00.unknown_08 + velocity.Z));
    return point.Length();
}
// @ref ??AMapClass@@QAEAAVCellClass@@ABUCoordStruct@@@Z=00548000
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
