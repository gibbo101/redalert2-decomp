// void MapClass::Unknown_0055A120() (0x0055A120)
// Unless the player's +0x188 is set: DisplayClass 0x0049E000 (false,
// false), +0x188 set, every cell of the global Map covered (+0x12C bits
// 3-4 and +0x140 bits 0-1 set, +0x130 and +0x134 cleared), DisplayClass
// 0x0049DE00 (false, false), the radar redrawn and a full redraw.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/house_screen.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Unknown_0049E000@DisplayClass@@QAEX_N0@Z=0049e000
// @ref ?Unknown_0049DE00@DisplayClass@@QAEX_N0@Z=0049de00
// @ref ?Unknown_00634030@RadarClass@@QAEXXZ=00634030
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0

void MapClass::Unknown_0055A120()
{
    if (!unknown_player_a35db4->unknown_188) {
        Map.Unknown_0049E000(false, false);
        unknown_player_a35db4->unknown_188 = true;
        Map.Unknown_0055A550();
        for (CellClass *cell = Map.Unknown_0055A490(); cell != 0; cell = Map.Unknown_0055A490()) {
            cell->unknown_12c |= 0x18;
            cell->unknown_130 = 0;
            cell->unknown_134 = 0;
            cell->unknown_140 |= 3;
        }
        Map.Unknown_0049DE00(false, false);
        Map.Unknown_00634030();
        Map.Flag_To_Redraw(2);
    }
}
