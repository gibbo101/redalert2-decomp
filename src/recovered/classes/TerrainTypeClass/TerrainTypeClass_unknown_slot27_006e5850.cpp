// CoordStruct TerrainTypeClass::unknown_slot27(CoordStruct const &coord) const (0x006E5850)
// The coordinate, raised to the ground height when below it.
#include "shared/terrain_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280

CoordStruct TerrainTypeClass::unknown_slot27(CoordStruct const &coord) const
{
    CoordStruct result = coord;
    if (result.Z < Map.Unknown_0055A280(result)) {
        result.Z = Map.Unknown_0055A280(result);
    }
    return result;
}
