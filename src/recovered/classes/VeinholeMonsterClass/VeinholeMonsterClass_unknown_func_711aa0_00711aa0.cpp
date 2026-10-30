#include "shared/veinhole.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/map_view.hpp"
#include "shared/anim.hpp"
// @ref ?unknown_cells_428ac0@@YAHXZ=00428ac0
// @ref ?unknown_cell_index_428a90@@YIHABVCell@@@Z=00428a90

void VeinholeMonsterClass::unknown_func_711aa0()
{
    unknown_98 = 0;
    unknown_9c->Clear();
    unknown_ec = 0;

    Map.Unknown_0055A550();
    CellClass *iter = Map.Unknown_0055A490();
    while (iter != 0) {
        if (iter->OverlayIndex == 0x7e && iter->OverlayData >= 0x30) {
            int index = unknown_cell_index_428a90(iter->MapCoords);
            if (index >= 0 && index < unknown_cells_428ac0() && unknown_b0[index]) {
                if (unknown_98 < Rules_Vein_Node_Count()) {
                    unknown_a0[unknown_98].Position = iter->MapCoords;
                    Point2D diff = Point2D(iter->MapCoords.X, iter->MapCoords.Y) - Point2D(Cell.X, Cell.Y);
                    unknown_a0[unknown_98].Key = 1000 - Cell_Distance(diff.X, diff.Y);
                    unknown_9c->Insert(&unknown_a0[unknown_98++]);
                    unknown_ec++;
                }
            }
        }
        iter = Map.Unknown_0055A490();
    }
}
