#include "shared/coord.hpp"
extern int unknown_map_min_a70a1c,unknown_map_max_a70a20;
// @ref ?unknown_map_min_a70a1c@@3HA=00a70a1c
// @ref ?unknown_map_max_a70a20@@3HA=00a70a20
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &cell)
{
    int x=cell.X;
    int y=cell.Y;
    return (x+y>unknown_map_min_a70a1c && x-y<unknown_map_min_a70a1c &&
           y-x<unknown_map_min_a70a1c && x+y<=unknown_map_max_a70a20) ? true : false;
}
