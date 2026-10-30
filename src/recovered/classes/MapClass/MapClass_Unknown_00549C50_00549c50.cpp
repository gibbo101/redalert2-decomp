// void MapClass::Unknown_00549C50(CoordStruct const &xcoord, int sightrange, HouseClass *house,
//     bool incremental, bool dont_map, bool unfog, bool byheight, bool arg8) (0x00549C50)
// Sight from a coordinate (TibSun Sight_From): the coordinate moved up the
// screen by its height, its cell on the map (0x0054AAB0) and a sight of 1-10;
// the radius offsets (0x00A6F248, ring counts 0x007A5908; with incremental
// and no reveal by height only the outer three rings) and their occlusion
// offsets (0x00A6ED18). The house is the player's when the player spies its
// radar or, with AllyReveal, is its ally; other houses do not map. Each cell
// within the sight (and, by height, not more than three levels below the
// occluding cell) loses +0x140 bit 6; unfog fogs mapped cells (Display slot
// 38), else unmapped cells are mapped unless dont_map (Radar slot 37 with
// arg8, else 0x0047C900). Finally 0x0054A550 with the sight + 3.
// The clamp tests 11 and then 10 (two compares in the original; MIN(10, MIN(sight, 11))
// compiles the same).
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_techno.hpp"
#include "shared/map_adjacent.hpp"
#include "shared/house_screen.hpp"
#include "shared/rules.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?unknown_radius_count_7a5908@@3QBHB=007a5908
// @ref ?unknown_radius_offset_a6f248@@3QBVCell@@B=00a6f248
// @ref ?unknown_occlusion_offset_a6ed18@@3QBVCell@@B=00a6ed18
// @ref ?Unknown_0054A550@MapClass@@QAEXABUCoordStruct@@HHH@Z=0054a550
// @ref ?unknown_slot38@DisplayClass@@QAE_NABVCell@@PAVHouseClass@@@Z=0049a0f0
// @ref ?unknown_slot37@RadarClass@@QAE_NABVCell@@PAVHouseClass@@_N@Z=0062fca0
// @ref ?unknown_47c900@CellClass@@QAEXXZ=0047c900
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Unknown_006A2970@@YIHH@Z=006a2970

// The sight scan tables (TibSun MapClass::RadiusCount, RadiusOffset, OcclusionOffset).
extern int const unknown_radius_count_7a5908[];
extern Cell const unknown_radius_offset_a6f248[];
extern Cell const unknown_occlusion_offset_a6ed18[];

void MapClass::Unknown_00549C50(CoordStruct const &xcoord, int sightrange, HouseClass *house, bool incremental, bool dont_map, bool unfog, bool byheight, bool arg8)
{
    int xx;
    Cell const *ptr;
    Cell const *ptr2;
    int count;

    int cell_height = xcoord.Z / unknown_geometry_g;

    CoordStruct coord = xcoord;
    coord.X = coord.X + (Unknown_006A2970(coord.Z) / -30) * 256;
    coord.Y = coord.Y + (Unknown_006A2970(coord.Z) / -30) * 256;

    Cell cell = Coord_Cell(coord);
    Cell hoffset = cell - Coord_Cell(xcoord) - Cell(2, 2);

    if (!Unknown_0054AAB0(cell)) return;
    if (!sightrange) return;
    if (sightrange >= 11 || sightrange > 10) sightrange = 10;

    xx = cell.X;

    count = unknown_radius_count_7a5908[sightrange];
    ptr = &unknown_radius_offset_a6f248[0];
    ptr2 = &unknown_occlusion_offset_a6ed18[0];
    if (!Rules->RevealByHeight && incremental) {
        if (sightrange > 2) {
            ptr += unknown_radius_count_7a5908[sightrange - 3];
            ptr2 += unknown_radius_count_7a5908[sightrange - 3];
            count -= unknown_radius_count_7a5908[sightrange - 3];
        }
    }
    ptr2--;

    if (house != 0 && unknown_player_a35db4 != 0) {
        if (house != unknown_player_a35db4) {
            if ((house->unknown_5414 & (1 << unknown_player_a35db4->Type->House)) != 0) {
                house = unknown_player_a35db4;
            }
        }
        if (house != unknown_player_a35db4) {
            if (house->Is_Ally(unknown_player_a35db4) && Rules->unknown_142b) {
                house = unknown_player_a35db4;
            }
        }
    }

    if (house != unknown_player_a35db4) {
        return;
    }

    while (count--) {
        Cell newcell;
        int xdiff;

        newcell = cell + *ptr++;
        ptr2++;

        if (!Unknown_0054AAB0(newcell)) continue;
        xdiff = newcell.X - xx;
        xdiff = abs(xdiff);
        if (xdiff > sightrange) continue;
        Cell delta = newcell - cell;
        if ((short)unknown_sqrt_4ba410((double)delta.X * delta.X + (double)delta.Y * delta.Y) > sightrange) continue;

        bool ok = false;
        CellClass *cellptr = &(*this)[newcell];
        if (byheight && Rules->RevealByHeight) {
            if (Map[newcell - hoffset + *ptr2].unknown_11b <= cell_height + 3) {
                ok = true;
            }
        } else {
            ok = true;
        }

        if (ok) {
            cellptr->unknown_140 &= ~0x40;
            if (unfog) {
                if ((!(cellptr->unknown_140 & 1) || !(cellptr->unknown_140 & 2)) && (cellptr->unknown_12c & 8)) {
                    Map.unknown_slot38(newcell, house);
                }
            } else {
                if ((!(cellptr->unknown_12c & 8) || !(cellptr->unknown_12c & 0x10) || !(cellptr->unknown_140 & 1) || !(cellptr->unknown_140 & 2)) && !dont_map) {
                    if (arg8) {
                        Map.unknown_slot37(newcell, house, false);
                    } else {
                        cellptr->unknown_47c900();
                    }
                }
            }
        }
    }

    Unknown_0054A550(coord, 0, sightrange + 3, 0);
}
