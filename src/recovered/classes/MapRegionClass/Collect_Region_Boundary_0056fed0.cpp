// DynamicVectorClass<Cell> *MapRegionClass::Collect_Region_Boundary_0056fed0() (0x0056FED0): a new list of the
// cells in this region's own cell list with at least one in-bounds 8-neighbour of another region.
#include "shared/map_region.hpp"
#include "shared/cell.hpp"

static inline bool In_Region_Bounds(Cell const &cell)
{
    int x = cell.X;
    int y = cell.Y;
    return y + x > unknown_map_min_a70a1c && x - y < unknown_map_min_a70a1c &&
        y - x < unknown_map_min_a70a1c && y + x <= unknown_map_max_a70a20;
}

DynamicVectorClass<Cell> *MapRegionClass::Collect_Region_Boundary_0056fed0()
{
    DynamicVectorClass<Cell> *cells = new DynamicVectorClass<Cell>;
    cells->Set_Growth_Step(10 > CellCount / 2 ? 10 : CellCount / 2);

    for (int i = Cells.Count() - 1; i >= 0; i--) {
        Cell cell = Cells[i];
        bool add = false;
        for (int facing = 0; facing < 8; facing++) {
            Cell ncell = cell + unknown_adjacent_851a70[facing & 7];
            if (In_Region_Bounds(ncell)) {
                if (UnknownMapGenerationCell::Get_Region(ncell) != Index) {
                    add = true;
                    break;
                }
            }
        }
        if (add) {
            cells->Add(cell);
        }
    }
    return cells;
}
