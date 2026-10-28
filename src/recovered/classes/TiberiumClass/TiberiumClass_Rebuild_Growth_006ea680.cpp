// void TiberiumClass::Rebuild_Growth() (0x006EA680)
// Queues every cell of the map that holds this tiberium and can grow, at score 0.
#include "shared/tiberium.hpp"
#include "shared/veinhole.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_cells_428ac0@@YAHXZ=00428ac0
// @ref ?unknown_cell_index_428a90@@YIHABVCell@@@Z=00428a90

void TiberiumClass::Rebuild_Growth()
{
    GrowthCount = 0;
    GrowthQueue->Clear();
    for (int index = unknown_cells_428ac0() - 1; index >= 0; index--) {
        GrowthMap[index] = false;
    }
    Map.Unknown_0055A550();
    for (CellClass *cell = Map.Unknown_0055A490(); cell != 0; cell = Map.Unknown_0055A490()) {
        if (cell->Get_Tiberium_Type() == ArrayIndex && cell->unknown_4788e0()) {
            GrowthData[GrowthCount].Position = cell->MapCoords;
            GrowthData[GrowthCount].Key = 0.0f;
            GrowthQueue->Insert(&GrowthData[GrowthCount++]);
            GrowthMap[unknown_cell_index_428a90(cell->MapCoords)] = true;
        }
    }
}
