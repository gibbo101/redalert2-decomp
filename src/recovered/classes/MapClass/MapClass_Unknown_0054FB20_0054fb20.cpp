// void MapClass::Unknown_0054FB20(Cell const &cell) (0x0054FB20)
// Updates one cell's zone after its passability changed (TibSun Update_Cell_Zone):
// a passable cell next to a passable neighbour with at most three zone changes
// around it joins that neighbour's zone; otherwise the zones are rebuilt
// (0x0054EBD0). Cells outside the map (kind 7) are left alone.
#include "shared/map.hpp"
#include "shared/map_view.hpp"

void MapClass::Unknown_0054FB20(Cell const &cell)
{
    UnknownMapElem4 *cell_data = &unknown_64[Unknown_0054FAB0(cell)];

    int stride = Map.MapSize.Width + Map.MapSize.Height + 1;
    int offsets[8] = {
        -(stride + 0),
        -(stride - 1),
        1,
        stride + 1,
        stride + 0,
        stride - 1,
        -1,
        -(stride + 1),
    };

    if (cell_data->unknown_00 != 7) {
        UnknownMapElem4 *land_neighbor = 0;
        bool has_land_neighbor = false;
        for (int i = 0; i < 8; i++) {
            land_neighbor = &cell_data[offsets[i]];
            if (land_neighbor->unknown_00 == 0) {
                has_land_neighbor = true;
                break;
            }
        }

        if (has_land_neighbor && land_neighbor != 0) {
            int transitions = 0;
            int prev_zone = 0;

            for (int j = 0; j < 8; j++) {
                UnknownMapElem4 *neighbor = &cell_data[offsets[j]];
                if (((unsigned short *)unknown_18[0])[neighbor->unknown_02] != ((unsigned short *)unknown_18[0])[prev_zone] && neighbor->unknown_00 != 7) {
                    prev_zone = neighbor->unknown_02;
                    transitions++;
                }
            }

            if (transitions <= 3 && cell_data->unknown_00 == 0) {
                cell_data->unknown_02 = land_neighbor->unknown_02;
                return;
            }
        }

        Map.Unknown_0054EBD0();
    }
}
