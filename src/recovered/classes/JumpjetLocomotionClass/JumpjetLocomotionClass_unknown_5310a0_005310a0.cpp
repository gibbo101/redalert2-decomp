// CoordStruct JumpjetLocomotionClass::unknown_5310a0(CoordStruct const &coord) (0x005310A0)
// The free spot near a coordinate (0x0049CB70); unless none, at ground
// height plus the bridge height on a bridge cell. Move_To expands it; this
// out-of-line copy has no callers (entry bounded by the preceding padding).
#include "shared/jumpjet_locomotion.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/cell.hpp"
// @ref ?unknown_coord_a6e3e0@@3UCoordStruct@@A=00a6e3e0

CoordStruct JumpjetLocomotionClass::unknown_5310a0(CoordStruct const &coord)
{
    CoordStruct result;
    result = Map.Unknown_0049CB70(coord, false);
    if (result != unknown_coord_a6e3e0) {
        result.Z = Map.Unknown_0055A280(result);
        if (Map[result].unknown_140 & 0x100) {
            result.Z += unknown_geometry_j;
        }
    }
    return result;
}
