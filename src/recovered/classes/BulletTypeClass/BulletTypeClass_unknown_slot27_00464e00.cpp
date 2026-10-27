// CoordStruct BulletTypeClass::unknown_slot27(CoordStruct const &coord) const (0x00464E00)
// The coordinate, raised above the ground height when it is not above it.
#include "shared/bullet_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280

CoordStruct BulletTypeClass::unknown_slot27(CoordStruct const &coord) const
{
    CoordStruct result = coord;
    if (result.Z <= Map.Unknown_0055A280(result)) {
        result.Z = Map.Unknown_0055A280(result) + 1;
    }
    return result;
}
