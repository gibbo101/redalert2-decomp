// void TiberiumClass::Rebuild_Spread() (0x006E9B90)
// Queues every cell of the map that holds this tiberium and can spread, at score 0.
#include "shared/tiberium.hpp"
#include "shared/veinhole.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_cells_428ac0@@YAHXZ=00428ac0
// @ref ?unknown_cell_index_428a90@@YIHABVCell@@@Z=00428a90

void TiberiumClass::Rebuild_Spread()
{
    SpreadCount = 0;
    SpreadQueue->Clear();
    for (int index = unknown_cells_428ac0() - 1; index >= 0; index--) {
        SpreadMap[index] = false;
    }
    Map.Unknown_0055A550();
    for (CellClass *cell = Map.Unknown_0055A490(); cell != 0; cell = Map.Unknown_0055A490()) {
        if (cell->Get_Tiberium_Type() == ArrayIndex && cell->unknown_478950()) {
            SpreadData[SpreadCount].Position = cell->MapCoords;
            SpreadData[SpreadCount].Score = 0.0f;
            SpreadQueue->Insert(&SpreadData[SpreadCount++]);
            SpreadMap[unknown_cell_index_428a90(cell->MapCoords)] = true;
        }
    }
}
