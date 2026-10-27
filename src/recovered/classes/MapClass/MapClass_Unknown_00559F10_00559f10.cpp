// void MapClass::Unknown_00559F10() (0x00559F10)
// Covers the whole map again: runs DisplayClass 0x0049E000 (false, false),
// clears every cell's visibility (+0x12C bits 3-4, +0x140 bits 0-1; +0x130
// set, +0x134 cleared), runs DisplayClass 0x0049DE00 (false, false), clears
// the player's +0x188, redraws the radar and flags a full redraw.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/house_screen.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Unknown_0049E000@DisplayClass@@QAEX_N0@Z=0049e000
// @ref ?Unknown_0049DE00@DisplayClass@@QAEX_N0@Z=0049de00
// @ref ?Unknown_00634030@RadarClass@@QAEXXZ=00634030

void MapClass::Unknown_00559F10()
{
    Map.Unknown_0049E000(false, false);
    Unknown_0055A550();
    for (CellClass *cell = Unknown_0055A490(); cell != 0; cell = Unknown_0055A490()) {
        cell->unknown_12c &= ~0x18;
        cell->unknown_130 = 1;
        cell->unknown_134 = 0;
        cell->unknown_140 &= ~3;
    }
    Map.Unknown_0049DE00(false, false);
    unknown_player_a35db4->unknown_188 = false;
    Map.Unknown_00634030();
    Flag_To_Redraw(2);
}
