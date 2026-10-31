// void TiberiumClass::Add_Spread_Cell(Cell const &cell) (0x006E9DD0)
// Queues a cell that can spread and is not queued yet, at the current frame plus a random 0-49
// (rebuilding the queue first when its table is nearly full).
#include "shared/tiberium.hpp"
#include "shared/veinhole.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/crt_memory.hpp"
// @ref ?unknown_cells_428ac0@@YIHXZ=00428ac0
// @ref ?unknown_cell_index_428a90@@YIHABVCell@@@Z=00428a90

void TiberiumClass::Add_Spread_Cell(Cell const &cell)
{
    int index = unknown_cell_index_428a90(cell);
    if (Map[cell].unknown_478950() && !SpreadMap[index]) {
        if (SpreadCount >= unknown_cells_428ac0() - 20) {
            Rebuild_Spread();
        }
        SpreadData[SpreadCount].Position = cell;
        SpreadData[SpreadCount].Key = abs(unknown_id_source_a3d290->Random()()) % 50 + Frame;
        SpreadQueue->Insert(&SpreadData[SpreadCount++]);
        SpreadMap[unknown_cell_index_428a90(cell)] = true;
    }
}
