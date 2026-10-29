// void UnitClass::unknown_slot87(CoordStruct const &source, bool forced, bool nokidding) (0x007072D0, slot 87)
// Scatter (hypothesis): moves the unit off its cell. Units that cannot move
// now (slot 155), teleporting units, units turning, units with a navigation
// target (unless nokidding) and units flagged at +0x5C8 stay. Without a
// source the unit takes the nearest free cell (0x005502E0) as its
// destination; otherwise, unless the mission is paralyzed, it is a unit
// flagged at +0x5B9, it is headed somewhere (and not told nokidding, or
// +0x599) or it has a target (and is not forced, three times in four), it
// tries the eight neighbouring cells starting from the direction away from
// the source (or its body facing) with a random -1..+1 turn, preferring one
// that the tactical view shows at the same cell and is not flagged 0x100,
// and moves there (mission 2).
#include "shared/crt_memory.hpp"
#include "shared/unit.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/fast_math.hpp"
#include "shared/teleport_locomotion.hpp"
// @ref ?unknown_cell_ad0488@@3VCell@@B=00ad0488
// @ref ?unknown_coord_ad04c0@@3UCoordStruct@@B=00ad04c0
// @ref ?unknown_level_height_ad0588@@3HA=00ad0588
// @ref ?unknown_facing_scale_79b628@@3NB=0079b628
// @ref ?unknown_facing_origin_79b630@@3NB=0079b630
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref _CLSID_TeleportLocomotionClass=007a1fd0
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref __com_issue_error@4=00795940
// @ref _unknown_uuid_IPersist_7cf208=007cf208
// @ref ?Query@?$UnknownComPtr@UIPersist@@$1?unknown_uuid_IPersist_7cf208@@3UGUID@@B@@QAEJABV?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@@Z=00454bf0
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_006A6A50@UnknownTacticalView@@QAE?AVCell@@ABUCoordStruct@@@Z=006a6a50
// @ref ?Unknown_005502E0@MapClass@@QAE?AVCell@@ABV2@HHH_NUPoint2D@@HHHH0H@Z=005502e0
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70

// The null cell and coordinate (0x00AD0488, 0x00AD04C0) and the height of
// one level (0x00AD0588): the unit's copies of shared/unknown_geometry.hpp's
// constants, which this file does not include (as UnitClass slot 55).
extern Cell const unknown_cell_ad0488;
extern CoordStruct const unknown_coord_ad04c0;
extern int unknown_level_height_ad0588;
// The direction scale (as UnknownFacingDir's coordinate constructor 0x00423EF0).
extern double const unknown_facing_scale_79b628;
extern double const unknown_facing_origin_79b630;

void UnitClass::unknown_slot87(CoordStruct const &source, bool forced, bool nokidding)
{
    if (!unknown_slot155()) {
        return;
    }
    UnknownComPtr<IPersist, &unknown_uuid_IPersist_7cf208> persist(Locomotor);
    GUID clsid;
    persist.Checked()->GetClassID(&clsid);
    if (memcmp(&clsid, &CLSID_TeleportLocomotionClass, sizeof(GUID)) == 0) {
        return;
    }
    if (!Control()->unknown_09 && !forced) {
        return;
    }
    if (unknown_2e0.Is_Rotating()) {
        return;
    }
    if (unknown_494 != 0 && !nokidding) {
        return;
    }
    if (unknown_5c8) {
        return;
    }
    if (source == unknown_coord_ad04c0) {
        Cell found = Map.Unknown_005502E0(Coord_Cell(unknown_slot19(0)), Type->SpeedType, -1, 0, unknown_79,
            Point2D(1, 1), 0, 1, 0, 1, Cell(0, 0), 0);
        if (found != unknown_cell_ad0488) {
            unknown_slot260(&Map[found], 1);
        }
    } else {
        if (Control()->unknown_07) {
            return;
        }
        if ((Kind_Of() != 1 || !unknown_5b9)
            && (unknown_494 == 0 || (nokidding && !unknown_599))
            && (unknown_228 == 0 || forced || Random_Pick(1, 4) == 1)) {
            int facing;
            if (source != unknown_coord_ad04c0) {
                CoordStruct here = Coord;
                UnknownFacingDir dir((unsigned short)((Fast_Atan2((double)source.Y - here.Y, (double)here.X - source.X)
                    - unknown_facing_origin_79b630) * unknown_facing_scale_79b628));
                facing = (Dir_To_8(dir) + Random_Pick(0, 2) - 1) & 7;
            } else {
                facing = (Dir_To_8(unknown_2e0.Current()) + Random_Pick(0, 2) - 1) & 7;
            }
            Cell alt(0, 0);
            Cell found(0, 0);
            Cell center = Coord_Cell(unknown_slot19(0));
            CellClass *cell = &Map[center];
            int level = (unknown_slot46(0) + cell->unknown_11b) ? 4 : 0;
            CoordStruct here = unknown_slot19(0);
            here.Z = unknown_level_height_ad0588 * level;
            for (int index = 0; index < 8; index++) {
                int dir = (facing + index) & 7;
                Cell adjacent = center + AdjacentCell[dir & 7];
                CellClass *next = &Map[adjacent];
                if (Map.Unknown_0055A660(adjacent, true) && unknown_slot101(next, dir, Unknown_005D47D0(), 0, 1) == 0) {
                    if (alt.X == unknown_cell_ad0488.X) {
                        if (alt.Y == unknown_cell_ad0488.Y) {
                            alt = adjacent;
                        }
                    }
                    if (found == unknown_cell_ad0488) {
                        CoordStruct coord = Cell_Center(adjacent);
                        coord.Z = here.Z;
                        if (adjacent == ((UnknownTacticalView *)unknown_tactical_83996c)->Unknown_006A6A50(coord)
                            && !(Map[adjacent].unknown_140 & 0x100)) {
                            found = adjacent;
                            break;
                        }
                    }
                }
            }
            Cell dest = found;
            if (found == unknown_cell_ad0488) {
                dest = alt;
            }
            if (dest != unknown_cell_ad0488) {
                unknown_slot116(2, false);
                unknown_slot260(&Map[dest], 1);
            }
        }
    }
}
