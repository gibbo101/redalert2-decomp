// CoordStruct InfantryTypeClass::unknown_slot27(CoordStruct const &coord) const (0x0050A9B0)
// The coordinate, raised to the ground height when below it.
#include "shared/infantry_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280

CoordStruct InfantryTypeClass::unknown_slot27(CoordStruct const &coord) const
{
    CoordStruct result = coord;
    if (result.Z < Map.Unknown_0055A280(result)) {
        result.Z = Map.Unknown_0055A280(result);
    }
    return result;
}
