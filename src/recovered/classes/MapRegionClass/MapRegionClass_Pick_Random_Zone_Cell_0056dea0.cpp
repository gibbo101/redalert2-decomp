// Cell __fastcall MapRegionClass::Pick_Random_Zone_Cell_0056dea0(int zone, int region) (0x0056DEA0, static; ECX hidden
// result, RET4): up to 99 random generation cells whose map cell is in movement zone zone (Map.Zone(.., 0, false)),
// passes unknown_47b590 and belongs to region (any when -1); else (0,0). Each pick is copied by value over the
// first generation cell (the original writes through the table pointer read at entry).
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/random2.hpp"
// @ref ?Zone@MapClass@@QAEHABVCell@@H_N@Z=0054f8f0
// @ref ?unknown_47b590@CellClass@@QBE_NXZ=0047b590
extern Random2Class unknown_map_random_a705c0;

Cell __fastcall MapRegionClass::Pick_Random_Zone_Cell_0056dea0(int zone, int region)
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
        CellClass &mapcell = Map[cell->Position];
        if (cell->Position.X == 0 && cell->Position.Y == 0) {
            continue;
        }
        if (Map.Zone(mapcell.MapCoords, 0, false) != zone) {
            continue;
        }
        if (!mapcell.unknown_47b590()) {
            continue;
        }
        if (region == -1 || cell->RegionIndex == region) {
            return cell->Position;
        }
    }
    return Cell(0, 0);
}
