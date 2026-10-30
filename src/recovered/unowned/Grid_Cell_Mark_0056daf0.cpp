#include "shared/map_region.hpp"
// @ref ?unknown_map_cell_side_84e804@@=0084e804
// @ref ?unknown_map_cells_a70a24@@=00a70a24
// Physical result is the raw AL byte, not a normalized bool.
unsigned char __fastcall Grid_Cell_Mark_0056daf0(Cell const &position)
{
    int index = (int)((unsigned)(int)position.Y * (unsigned)unknown_map_cell_side_84e804 + (unsigned)(int)position.X);
    return unknown_map_cells_a70a24[index].Marked;
}
