#include "shared/veinhole.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_func_711aa0@VeinholeMonsterClass@@QAEXXZ=00711aa0

void VeinholeMonsterClass::unknown_func_711d20()
{
    CellClass &cptr = Map[Cell];
    cptr.OverlayIndex = 0x7e;
    cptr.OverlayData = 0;
    cptr.Unknown_00472540(-1);
    for (int dir = 0; dir < 8; dir++) {
        CellClass &adj = cptr.Adjacent_Cell(dir);
        if (dir % 2 != 0) {
            adj.OverlayIndex = -1;
            adj.OverlayData = 0;
        } else {
            adj.OverlayIndex = 0x7e;
            adj.OverlayData = 0;
        }
    }
    for (int y = -2; y <= 2; y++) {
        for (int x = -2; x <= 2; x++) {
            CellClass &cptr2 = Map[::Cell(x, y) + Cell];
            cptr2.unknown_47ad00();
            cptr2.Unknown_00472540(-1);
        }
    }
    unknown_func_711aa0();
    Map.Unknown_0054FB20(Cell);
    Map.Unknown_00566340(Cell);
    unknown_e8 = true;
}
