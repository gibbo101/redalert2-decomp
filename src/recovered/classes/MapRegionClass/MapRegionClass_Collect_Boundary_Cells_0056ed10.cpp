// DynamicVectorClass<Cell> *MapRegionClass::Collect_Boundary_Cells_0056ed10() (0x0056ED10): a new list of the
// cells of this region (in map walk order) with at least one in-bounds 8-neighbour of another region.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_map_cell_side_84e804@@3HA=0084e804
// @ref ?unknown_map_cells_a70a24@@3PAUUnknownMapGenerationCell@@A=00a70a24
// @ref ?unknown_map_min_a70a1c@@3HA=00a70a1c
// @ref ?unknown_map_max_a70a20@@3HA=00a70a20
// @ref ??0?$VectorClass@VCell@@@@QAE@IPBVCell@@@Z=0042d4a0
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
// @ref ?Adjacent_Cell@CellClass@@QAEAAV1@I@Z=00476ac0
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490

// The 8-neighbour bounds test of the generation diamond, written as an inline helper.
static inline bool In_Generation_Bounds(Cell const &next)
{
    int x = next.X;
    int y = next.Y;
    return y + x > unknown_map_min_a70a1c && x - y < unknown_map_min_a70a1c &&
        y - x < unknown_map_min_a70a1c && y + x <= unknown_map_max_a70a20;
}

DynamicVectorClass<Cell> *MapRegionClass::Collect_Boundary_Cells_0056ed10()
{
    DynamicVectorClass<Cell> *cells = new DynamicVectorClass<Cell>;
    Map.Unknown_0055A550();
    for (CellClass *cell = Map.Unknown_0055A490(); cell != 0; cell = Map.Unknown_0055A490()) {
        Cell position = cell->MapCoords;
        if (UnknownMapGenerationCell::Get_Region(position) != Index) {
            continue;
        }
        bool edge = false;
        for (int direction = 0; direction < 8; direction++) {
            CellClass &adjacent = cell->Adjacent_Cell(direction);
            Cell next = adjacent.MapCoords;
            if (In_Generation_Bounds(next)) {
                if (UnknownMapGenerationCell::Get_Region(next) != Index) {
                    edge = true;
                }
            }
        }
        if (edge) {
            Cell coords = cell->MapCoords;
            cells->Add(coords);
        }
    }
    return cells;
}
