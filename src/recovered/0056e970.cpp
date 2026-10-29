// 0056E970: conditionally assign a map-generation grid cell's region index.
// Accepted-provider migration approved by owner; exact compile is the gate.
// Physical contract: ECX -> signed16 X/Y, EDX -> raw32 stored at grid+38,
// RET0, no defined return value. Name, const-reference and int intent are hypotheses.
#include "shared/map_region.hpp"
// @ref ?unknown_map_cell_side_84e804@@3HA=0084e804
// @ref ?unknown_map_cells_a70a24@@3PAUUnknownMapGenerationCell@@A=00a70a24
void __fastcall Set_Cell_Region_Index_0056e970(Cell const &position, int index)
{
    UnknownMapGenerationCell *cells = unknown_map_cells_a70a24;
    if (cells) {
        unsigned int row = position.Y;
        row *= unknown_map_cell_side_84e804;
        unsigned int slot = position.X;
        slot += row;
        cells[slot].RegionIndex = index;
    }
}
