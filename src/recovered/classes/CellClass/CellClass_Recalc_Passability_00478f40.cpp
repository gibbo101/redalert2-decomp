// void CellClass::unknown_478f40() (0x00478F40): Westwood's Recalc_Passability. Sets unknown_4c
// (Passability: 0 land, 1 crush, 2 blocked, 3 beach, 4 water, 5 partially blocked, 6 impassable,
// 7 outside the local radar) from the overlay, the land and the occupiers.
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/overlay_type.hpp"
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/house.hpp"
#include "shared/terrain.hpp"
#include "shared/terrain_type.hpp"

void CellClass::unknown_478f40()
{
    if (!Map.Unknown_0055A660(MapCoords, true)) {
        unknown_4c = 7;
        return;
    }

    if (OverlayIndex != -1) {
        OverlayTypeClass const *overlay = OverlayTypes[OverlayIndex];
        if (overlay->unknown_1fd) {
            unknown_4c = 1;
            return;
        }
        if (overlay->Wall) {
            unknown_4c = 2;
            return;
        }
        if (Ground[overlay->Land].Cost[2] == 0) {
            unknown_4c = 6;
            return;
        }
        if (overlay->IsARock) {
            unknown_4c = 6;
            return;
        }
        if (overlay->IsRubble) {
            unknown_4c = 0;
            return;
        }
    }

    if (unknown_ec == 2) {
        unknown_4c = 4;
        return;
    }
    if (unknown_ec == 6) {
        unknown_4c = 3;
        return;
    }

    if (Ground[unknown_ec].Cost[2] <= 0.01) {
        unknown_4c = 6;
        return;
    }

    for (ObjectClass *occupier = OccupierPtr; occupier != 0; occupier = occupier->unknown_30) {
        switch (occupier->Kind_Of()) {
            case 6:
                if (((BuildingClass *)occupier)->Type->FirestormWall) {
                    if (((BuildingClass *)occupier)->House->unknown_142) {
                        unknown_4c = 6;
                        return;
                    }
                } else if (((BuildingClass *)occupier)->Type->LaserFence) {
                    if (((BuildingClass *)occupier)->unknown_4ec != 12 && ((BuildingClass *)occupier)->unknown_4ec != 8) {
                        unknown_4c = 6;
                    }
                }
                break;

            case 0x24:
                if ((unknown_id_source_a3d290->Theater != 1 && ((TerrainClass *)occupier)->Class->TemperateOccupationBits != 7)
                    || (unknown_id_source_a3d290->Theater == 1 && ((TerrainClass *)occupier)->Class->SnowOccupationBits != 7)) {
                    unknown_4c = 5;
                    return;
                }
                unknown_4c = 2;
                return;
        }
    }

    unknown_4c = 0;
}
