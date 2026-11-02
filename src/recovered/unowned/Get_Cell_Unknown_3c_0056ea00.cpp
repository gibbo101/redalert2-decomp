// 0056EA00: read a map-generation grid cell's +3C word (getter beside the 0056E9D0 setter).
// Physical contract: ECX -> signed16 X/Y, EAX <- raw32 at grid+3C, RET0, no null check.
// Name, const-reference and int intent are hypotheses; unreferenced in the image.
#include "shared/map_region.hpp"
// @ref ?unknown_map_cell_side_84e804@@3HA=0084e804
// @ref ?unknown_map_cells_a70a24@@3PAUUnknownMapGenerationCell@@A=00a70a24
int __fastcall Get_Cell_Unknown_3c_0056ea00(Cell const &position)
{
    return unknown_map_cells_a70a24[position.Y * unknown_map_cell_side_84e804 + position.X].unknown_3c;
}
