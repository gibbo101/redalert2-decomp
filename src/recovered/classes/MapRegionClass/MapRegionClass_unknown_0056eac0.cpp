// void MapRegionClass::unknown_0056eac0(int count, int mark) (0x0056EAC0, RET8): sets RegionIndex to mark
// on count rings of generation cells, starting with this region's boundary cells and growing each ring by the
// 8-neighbours of this region not yet in a ring (+0x3C holds the ring number; cleared before and after when
// count > 1).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_SET_GROWTH_STEP
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/map_region.hpp"
// @ref ?unknown_map_cell_side_84e804@@3HA=0084e804
// @ref ?unknown_map_cells_a70a24@@3PAUUnknownMapGenerationCell@@A=00a70a24
// @ref ?unknown_map_min_a70a1c@@3HA=00a70a1c
// @ref ?unknown_map_max_a70a20@@3HA=00a70a20
// @ref ?unknown_adjacent_851a70@@3QBVCell@@B=00851a70
// @ref ?Collect_Boundary_Cells_0056ed10@MapRegionClass@@=0056ed10
// @ref ??0?$VectorClass@VCell@@@@QAE@IPBVCell@@@Z=0042d4a0
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0

void MapRegionClass::unknown_0056eac0(int count, int mark)
{
    DynamicVectorClass<Cell> *ring = Collect_Boundary_Cells_0056ed10();
    if (count > 1) {
        int total = unknown_map_cell_side_84e804 * unknown_map_cell_side_84e804;
        for (int i = 0; i < total; i++) {
            unknown_map_cells_a70a24[i].unknown_3c = -1;
        }
    }
    for (int step = 0; step < count; step++) {
        int index;
        for (index = ring->Count() - 1; index >= 0; index--) {
            Cell cell = (*ring)[index];
            if (unknown_map_cells_a70a24) {
                unknown_map_cells_a70a24[cell.Y * unknown_map_cell_side_84e804 + cell.X].RegionIndex = mark;
            }
        }
        if (step < count - 1) {
            DynamicVectorClass<Cell> *next = new DynamicVectorClass<Cell>;
            next->Set_Growth_Step(ring->Count());
            for (index = ring->Count() - 1; index >= 0; index--) {
                Cell cell = (*ring)[index];
                for (int direction = 0; direction < 8; direction++) {
                    Cell const &offset = unknown_adjacent_851a70[direction & 7];
                    Cell adjacent = cell + offset;
                    if (adjacent.Y + adjacent.X > unknown_map_min_a70a1c && adjacent.X - adjacent.Y < unknown_map_min_a70a1c &&
                        adjacent.Y - adjacent.X < unknown_map_min_a70a1c && adjacent.Y + adjacent.X <= unknown_map_max_a70a20) {
                        UnknownMapGenerationCell &data = unknown_map_cells_a70a24[adjacent.Y * unknown_map_cell_side_84e804 + adjacent.X];
                        if (data.RegionIndex == Index && data.unknown_3c != step + 1) {
                            next->Add(adjacent);
                            data.unknown_3c = step + 1;
                        }
                    }
                }
            }
            delete ring;
            ring = next;
        }
    }
    delete ring;
    if (count > 1) {
        int total = unknown_map_cell_side_84e804 * unknown_map_cell_side_84e804;
        for (int i = 0; i < total; i++) {
            unknown_map_cells_a70a24[i].unknown_3c = -1;
        }
    }
}
