// Cell MapRegionClass::Pick_Random_Region_Cell_0056dc20() (0x0056DC20): a random generation-grid cell that
// belongs to this region and is not the (0,0) placeholder. The inner loop is Map_Random_Range_005797a0(0, count - 1)
// (0x005797A0, Map_Random_Fraction_00579770 inline) as written in the region-generation unit.
#include "shared/map_region.hpp"
#include "shared/random2.hpp"
// @ref ?unknown_map_cell_side_84e804@@=0084e804
// @ref ?unknown_map_cells_a70a24@@=00a70a24
// @ref ?unknown_map_random_a705c0@@3VRandom2Class@@A=00a705c0
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref __ftol=0077f110
extern Random2Class unknown_map_random_a705c0;

Cell MapRegionClass::Pick_Random_Region_Cell_0056dc20()
{
    int count = unknown_map_cell_side_84e804 * unknown_map_cell_side_84e804;
    unsigned int index;
    do {
        unsigned int maximum = count - 1;
        do {
            index = (unsigned int)((unsigned int)unknown_map_random_a705c0() * (1.0 / 4294967295.0) * (unsigned int)(maximum + 1) + (double)0);
        } while (index > maximum);
    } while (unknown_map_cells_a70a24[index].RegionIndex != Index
        || (unknown_map_cells_a70a24[index].Position.X == 0 && unknown_map_cells_a70a24[index].Position.Y == 0));
    return unknown_map_cells_a70a24[index].Position;
}
