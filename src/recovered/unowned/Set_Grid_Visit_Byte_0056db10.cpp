#include "shared/map_region.hpp"
// Physical ECX points to packed signed-WORD Cell; source signature/name are hypotheses.
// @ref ?unknown_map_cell_side_84e804@@=0084e804
// @ref ?unknown_map_cells_a70a24@@=00a70a24
void __fastcall Set_Grid_Visit_Byte_0056db10(Cell const &position)
{
    int index = (int)((unsigned)(int)position.Y * (unsigned)unknown_map_cell_side_84e804 + (unsigned)(int)position.X);
    unknown_map_cells_a70a24[index].unknown_45[0] = 1;
}
