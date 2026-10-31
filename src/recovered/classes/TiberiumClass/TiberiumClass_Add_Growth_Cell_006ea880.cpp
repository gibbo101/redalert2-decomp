// void TiberiumClass::Add_Growth_Cell(Cell const &cell) (0x006EA880)
// Queues a cell whose ore is below its last stage, at the current frame plus a random 0-49
// (rebuilding the queue first when its table is nearly full).
#include "shared/tiberium.hpp"
#include "shared/veinhole.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/crt_memory.hpp"
// @ref ?unknown_cells_428ac0@@YIHXZ=00428ac0
// @ref ?unknown_cell_index_428a90@@YIHABVCell@@@Z=00428a90

void TiberiumClass::Add_Growth_Cell(Cell const &cell)
{
    int index = unknown_cell_index_428a90(cell);
    if (Map[cell].OverlayData < 11) {
        if (GrowthCount > unknown_cells_428ac0() - 10) {
            Rebuild_Growth();
        }
        GrowthData[GrowthCount].Position = cell;
        GrowthData[GrowthCount].Key = abs(unknown_id_source_a3d290->Random()()) % 50 + Frame;
        GrowthQueue->Insert(&GrowthData[GrowthCount++]);
        GrowthMap[index] = true;
    }
}
