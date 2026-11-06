// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// void MapClass::Mark_Fill_Area(Cell const &origin, bool on_water) (0x00567710)
// TibSun Mark_Fill_Area: floods out from the origin over water cells (on_water) or
// clear cells of the origin's height, marking the generator records' +0x49 (in the
// fill area), then marks +0x4A (in reach) on the 3 x 3 block around every filled cell.
// From ra2-decomp MapClass::Mark_Fill_Area (YR 0x00585930), adapted to our names.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_region.hpp"
#include "shared/map_adjacent.hpp"
// @ref ?Get_Cell_Data_0056dbc0@@YIAAUUnknownMapGenerationCell@@H@Z=0056dbc0
// @ref ?Get_Cell_Data_0056dba0@@YIAAUUnknownMapGenerationCell@@ABVCell@@@Z=0056dba0
// @ref ?Add@?$DynamicVectorClass@VCell@@@@QAE_NABVCell@@@Z=0056ba30
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
// @ref ??_7?$VectorClass@VCell@@@@6B@=0079c5e0
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ??H?$TPoint2D@F@@QBE?BV0@ABV0@@Z=0042add0
// @ref ?unknown_47b7e0@CellClass@@QBE_NXZ=0047b7e0

void MapClass::Mark_Fill_Area(Cell const &origin, bool on_water)
{
    DynamicVectorClass<Cell> region_cells;
    region_cells.Clear();
    region_cells.Set_Growth_Step(100);

    DynamicVectorClass<Cell> frontier_cells;
    frontier_cells.Clear();
    frontier_cells.Set_Growth_Step(1000);

    for (int i = unknown_map_cell_side_84e804 * unknown_map_cell_side_84e804 - 1; i >= 0; i--) {
        UnknownMapGenerationCell &data = Get_Cell_Data_0056dbc0(i);
        data.unknown_45[4] = 0;
        data.unknown_45[5] = 0;
    }

    frontier_cells.Add(origin);
    region_cells.Add(origin);

    if (Unknown_0054AAB0(origin)) {
        Get_Cell_Data_0056dba0(origin).unknown_45[4] = 1;
    }

    int height = Map[origin].unknown_11b;

    while (frontier_cells.Count()) {
        Cell cell = frontier_cells[frontier_cells.Count() - 1];
        frontier_cells.Delete(frontier_cells.Count() - 1);

        for (int dir = 0; dir < 8; dir++) {
            Cell adjacent = Adjacent_Cell(cell, dir);
            if (Unknown_0054AAB0(adjacent)) {
                UnknownMapGenerationCell &data = Get_Cell_Data_0056dba0(adjacent);
                CellClass *adjptr = &Map[adjacent];
                if (!data.unknown_45[4]) {
                    if (on_water && adjptr->unknown_47b7e0() || !on_water && adjptr->unknown_11b == height && adjptr->unknown_47b590()) {
                        frontier_cells.Add(adjacent);
                        bool legal = Unknown_0054AAB0(adjacent);
                        bool legal2 = Unknown_0054AAB0(cell);
                        region_cells.Add(adjacent);
                        data.unknown_45[4] = 1;
                    }
                }
            }
        }
    }

    for (int j = 0; j < region_cells.Count(); j++) {
        Cell cell = region_cells[j];
        for (int y = cell.Y - 1; y < cell.Y + 2; y++) {
            for (int x = cell.X - 1; x < cell.X + 2; x++) {
                Cell influence;
                influence.X = x;
                influence.Y = y;
                if (Unknown_0054AAB0(influence)) {
                    Get_Cell_Data_0056dba0(Cell(x, y)).unknown_45[5] = 1;
                }
            }
        }
    }
}
