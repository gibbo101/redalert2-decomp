// int MapClass::Region_Threat(HouseClass *house, int level, int from_subzone, int to_subzone) (0x00567D20)
// TibSun Region_Threat: the threat between two subzones' threat regions.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/house_screen.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_cells_a6f218@@3PAVCell@@A=00a6f218
// @ref ?unknown_from_quadrants_7e0494@@3PAY01HA=007e0494
// @ref ?unknown_to_quadrants_7e04d4@@3PAY01HA=007e04d4

extern int unknown_from_quadrants_7e0494[8][2];
extern int unknown_to_quadrants_7e04d4[8][2];

int MapClass::Region_Threat(HouseClass *house, int level, int from_subzone, int to_subzone)
{
    switch (level) {
        default:
            break;

        case 0:
            return 0;

        case 1:
            return house->unknown_56d0[Map.SubzoneTracking[level][to_subzone].unknown_20];

        case 2: {
            int from_region = Map.SubzoneTracking[level][from_subzone].unknown_20;
            int index = from_region - 1;
            int col = index % 130;
            int row = (from_region - col) / 130;
            int from_x = 4 * col;
            int from_y = 4 * (row - 1);

            short from_block_x = from_x - (from_x / 4 % 2 != 0);
            short from_block_y = from_y - (from_y / 4 % 2 != 0);

            int to_region = Map.SubzoneTracking[level][to_subzone].unknown_20;
            index = to_region - 1;
            col = index % 130;
            row = (to_region - col) / 130;
            int to_x = 4 * col;
            int to_y = 4 * (row - 1);

            short to_block_x = to_x - (to_x / 4 % 2 != 0);
            short to_block_y = to_y - (to_y / 4 % 2 != 0);

            if (from_block_x == to_block_x && from_block_y == to_block_y) {
                return (house->unknown_56d0[Unknown_0054E370(XY_Cell(from_x, from_y))] + house->unknown_56d0[Unknown_0054E370(XY_Cell(to_x, to_y))]) >> 1;
            }

            int facing;
            if (to_block_x > from_block_x) {
                if (to_block_y > from_block_y) {
                    facing = 3;
                } else if (to_block_y >= from_block_y) {
                    facing = 2;
                } else {
                    facing = 1;
                }
            } else if (to_block_x < from_block_x) {
                if (to_block_y > from_block_y) {
                    facing = 5;
                } else if (to_block_y >= from_block_y) {
                    facing = 6;
                } else {
                    facing = 7;
                }
            } else if (to_block_y > from_block_y) {
                facing = 4;
            } else {
                facing = 0;
            }

            int from_threat1 = house->unknown_56d0[Unknown_0054E370(XY_Cell(from_block_x, from_block_y) + unknown_cells_a6f218[unknown_from_quadrants_7e0494[facing][0]])];
            int from_threat2 = house->unknown_56d0[Unknown_0054E370(unknown_cells_a6f218[unknown_from_quadrants_7e0494[facing][1]] + XY_Cell(from_block_x, from_block_y))];
            int from_threat = from_threat1;
            if (from_threat1 >= from_threat2) {
                from_threat = from_threat2;
            }

            int to_threat1 = house->unknown_56d0[Unknown_0054E370(unknown_cells_a6f218[unknown_to_quadrants_7e04d4[facing][0]] + XY_Cell(to_block_x, to_block_y))];
            int to_threat2 = house->unknown_56d0[Unknown_0054E370(unknown_cells_a6f218[unknown_to_quadrants_7e04d4[facing][1]] + XY_Cell(to_block_x, to_block_y))];
            if (to_threat1 >= to_threat2) {
                to_threat1 = to_threat2;
            }

            return (to_threat1 + from_threat) >> 1;
        }
    }
    return 0;
}
