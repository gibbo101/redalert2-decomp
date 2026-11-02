// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __ftol=0077f110
// @ref _unknown_geometry_g=00a6fc30
// @ref ?Sight_From@MapClass@@QAEXABUCoordStruct@@HPAVHouseClass@@_N2222@Z=0054a110
// Sight scan0054A110, complete1088+0. Shares the owned accepted549C50 scan layout.
// unknown_arg5 is not read; original flags unfog and arg8 have byte-valued bool ABI.
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
// @ref ?unknown_slot38@DisplayClass@@QAE_NABVCell@@PAVHouseClass@@@Z=0049a0f0
// @ref ?unknown_slot37@RadarClass@@QAE_NABVCell@@PAVHouseClass@@_N@Z=0062fca0
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Unknown_006A2970@@YIHH@Z=006a2970

// The sight scan tables (TibSun MapClass::RadiusCount, RadiusOffset, OcclusionOffset).
extern int const unknown_radius_count_7a5908[];
extern Cell const unknown_radius_offset_a6f248[];
extern Cell const unknown_occlusion_offset_a6ed18[];

void MapClass::Sight_From(CoordStruct const &xcoord, int sightrange, HouseClass *house, bool incremental, bool unknown_arg5, bool unfog, bool byheight, bool arg8)
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
                Map.unknown_slot37(newcell, house, arg8);
            }
        }
    }

}
