// void TiberiumClass::Process_Spread() (0x006E9720)
// Spreads ore from up to 5-25 queued cells (a random share of the queue's SpreadPercentage); a cell
// with more than one open neighbour is queued again at score 0 (TibSun Spread_AI).
#include "shared/tiberium.hpp"
#include "shared/veinhole.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/dir_type.hpp"
#include "shared/incdec.hpp"
// @ref ?unknown_cells_428ac0@@YIHXZ=00428ac0
// @ref ?unknown_cell_index_428a90@@YIHABVCell@@@Z=00428a90
// @ref ?Rebuild_Spread@TiberiumClass@@QAEXXZ=006e9b90
// @ref ?Sift_Down@UnknownVeinHeap@@QAEXH@Z=0058f090
// @ref __real@8@3feea7c5ac471b478800=0079c520

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

void TiberiumClass::Process_Spread()
{
    if (SpreadQueue != 0 && SpreadQueue->Count != 0 && unknown_a0 > 0.00001) {
        int count = MIN(25, MAX(5, (int)(SpreadQueue->Count * unknown_a0)));
        count = abs(unknown_id_source_a3d290->Random()()) % count + 1;
        if (SpreadQueue->Active_Count() > unknown_cells_428ac0() - 20) {
            Rebuild_Spread();
        }
        int index = 0;
        UnknownVeinNode *node = SpreadQueue->Remove_Min();
        while (index < count && node != 0) {
            CellClass *cellptr = &Map[node->Position];
            int possible = 0;
            for (FacingType facing = FACING_N; facing < FACING_COUNT; facing++) {
                CellClass &adjacent = cellptr->Adjacent_Cell(facing);
                if (adjacent.unknown_478ba0(false)) {
                    possible++;
                }
            }
            if (possible != 0) {
                cellptr->unknown_478a40(0);
                index++;
                if (possible > 1) {
                    SpreadData[SpreadCount].Position = cellptr->MapCoords;
                    SpreadData[SpreadCount].Key = 0.0f;
                    SpreadQueue->Insert(&SpreadData[SpreadCount++]);
                    SpreadMap[unknown_cell_index_428a90(cellptr->MapCoords)] = true;
                }
            } else {
                SpreadMap[unknown_cell_index_428a90(cellptr->MapCoords)] = false;
            }
            if (index < count) {
                node = SpreadQueue->Remove_Min();
            }
        }
    }
}
