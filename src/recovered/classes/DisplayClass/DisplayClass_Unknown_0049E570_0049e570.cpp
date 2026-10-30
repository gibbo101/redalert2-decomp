// void DisplayClass::Unknown_0049E570() (0x0049E570)
// After 0x00529720, runs 0x004790F0 (0, 0x10000, 0, 1000, 1000, 1000) on every
// cell of the map with 0x00A6FA2C cleared, then asks for a full redraw.
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550
// @ref ?Reset_Light_Converts_00529720@@YAXXZ=00529720
// @ref ?Init_Drawer@CellClass@@QAEXPAVLightConvertClass@@HHHHH@Z=004790f0
// @ref ?unknown_int_a6fa2c@@3HA=00a6fa2c

extern int unknown_int_a6fa2c;      // 0x00A6FA2C

void DisplayClass::Unknown_0049E570()
{
    Reset_Light_Converts_00529720();
    Map.Unknown_0055A550();
    CellClass *cell = Map.Unknown_0055A490();
    unknown_int_a6fa2c = 0;
    while (cell) {
        cell->Init_Drawer(0, 0x10000, 0, 1000, 1000, 1000);
        cell = Map.Unknown_0055A490();
    }
    Flag_To_Redraw(true);
}
