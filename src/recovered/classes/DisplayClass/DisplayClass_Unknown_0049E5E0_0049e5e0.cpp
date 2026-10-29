// void DisplayClass::Unknown_0049E5E0() (0x0049E5E0)
// Runs 0x004798F0 on every cell of the map.
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550
// @ref ?Unknown_004798F0@CellClass@@QAEXXZ=004798f0

void DisplayClass::Unknown_0049E5E0()
{
    Map.Unknown_0055A550();
    for (CellClass *cell = Map.Unknown_0055A490(); cell; cell = Map.Unknown_0055A490()) {
        cell->Unknown_004798F0();
    }
}
