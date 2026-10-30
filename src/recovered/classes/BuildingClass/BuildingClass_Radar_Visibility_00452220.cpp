// Radar visibility: discovery, cloak/fog and sensing checks.
#include "shared/building.hpp"
#include "shared/building_map.hpp"
#include "shared/house.hpp"
// @ref ?Unknown_004F52B0@HouseClass@@=004f52b0
// @ref ?Foundation_Height@BuildingTypeClass@@=00458940
// @ref ?Width@BuildingTypeClass@@=00458930
// @ref ?Unknown_00568140@MapClass@@=00568140
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?unknown_player_a35db4@@=00a35db4
// @ref ?unknown_b263d8@@=00b263d8

bool BuildingClass::unknown_slot190(int *out_kind)
{
    if (!Type->Invisible) {
        if (Type->RadarVisible) return true;
        if (House->Unknown_004F52B0()) return unknown_373 ? true : false;
        int height = Type->Foundation_Height(false) * 256 - 256;
        int width = Type->Width() * 256 - 256;
        bool shrouded = Map.Unknown_00568140(CoordStruct(Coord))
            && Map.Unknown_00568140(CoordStruct(Coord) + CoordStruct(width, height, 0))
            && unknown_b263d8;
        if (unknown_1b8 != 2 && unknown_5bd != 15 && !unknown_5b7 && !shrouded) return true;
        if (!unknown_slot191()) return false;
        if (!unknown_player_a35db4->Is_Ally(House) && !unknown_5b7 && !shrouded) *out_kind = 1;
        return true;
    }
    return false;
}
