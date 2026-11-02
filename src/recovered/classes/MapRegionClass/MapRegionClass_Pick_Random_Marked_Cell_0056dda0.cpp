// Cell MapRegionClass::Pick_Random_Marked_Cell_0056dda0() (0x0056DDA0, RET4 hidden result): up to 99 random
// generation cells of this region that are not (0,0), are Marked and whose map cell passes unknown_47b590; else
// (0,0). Each pick is copied by value over the first generation cell (as 0x0056DEA0).
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/random2.hpp"
// @ref ?unknown_47b590@CellClass@@QBE_NXZ=0047b590
#include "shared/map_random.hpp"

Cell MapRegionClass::Pick_Random_Marked_Cell_0056dda0()
{
    UnknownMapGenerationCell *cell = unknown_map_cells_a70a24;
    int count = unknown_map_cell_side_84e804 * unknown_map_cell_side_84e804;
    int tries = 0;
    for (;;) {
        unsigned int maximum = count - 1;
        unsigned int index;
        do {
            index = (unsigned int)((unsigned int)unknown_map_random_a705c0() * (1.0 / 4294967295.0) * (unsigned int)(maximum + 1) + (double)0);
        } while (index > maximum);
        *cell = unknown_map_cells_a70a24[index];
        if (++tries >= 100) {
            break;
        }
        if (cell->RegionIndex != Index) {
            continue;
        }
        if (cell->Position.X == 0 && cell->Position.Y == 0) {
            continue;
        }
        if (!cell->Marked) {
            continue;
        }
        if (Map[cell->Position].unknown_47b590()) {
            return cell->Position;
        }
    }
    return Cell(0, 0);
}
