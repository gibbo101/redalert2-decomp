// void TiberiumClass::Process_Growth() (0x006EA1E0)
// Grows the ore of up to 5-50 queued cells (a random share of the queue's GrowthPercentage); a cell
// below the last stage is queued again 0-49 frames later and offered to the spread queue (TibSun
// Growth_AI).
#include "shared/tiberium.hpp"
#include "shared/veinhole.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_cells_428ac0@@YIHXZ=00428ac0
// @ref ?unknown_cell_index_428a90@@YIHABVCell@@@Z=00428a90
// @ref ?Rebuild_Growth@TiberiumClass@@QAEXXZ=006ea680
// @ref ?Add_Spread_Cell@TiberiumClass@@QAEXABVCell@@@Z=006e9dd0
// @ref ?Sift_Down@UnknownVeinHeap@@QAEXH@Z=0058f090
// @ref __real@8@3feea7c5ac471b478800=0079c520

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

void TiberiumClass::Process_Growth()
{
    if (GrowthQueue != 0 && GrowthQueue->Active_Count() != 0 && unknown_b0 > 0.00001) {
        int count = MIN(50, MAX(5, (int)(GrowthQueue->Active_Count() * unknown_b0)));
        count = abs(unknown_id_source_a3d290->Random()()) % count + 1;
        if (GrowthQueue->Active_Count() > unknown_cells_428ac0() - 2 * count) {
            Rebuild_Growth();
        }
        int index = 0;
        UnknownVeinNode *node = GrowthQueue->Remove_Min();
        while (index < count && node != 0) {
            CellClass *cellptr = &Map[node->Position];
            if (cellptr->Get_Tiberium_Type() == ArrayIndex) {
                cellptr->unknown_4789d0();
                if (cellptr->OverlayData < 11) {
                    GrowthData[GrowthCount].Position = node->Position;
                    GrowthData[GrowthCount].Key = float(Frame + abs(unknown_id_source_a3d290->Random()() % 50));
                    GrowthMap[unknown_cell_index_428a90(node->Position)] = true;
                    GrowthQueue->Insert(&GrowthData[GrowthCount++]);
                    Add_Spread_Cell(node->Position);
                } else {
                    GrowthMap[unknown_cell_index_428a90(node->Position)] = false;
                }
            }
            index++;
            if (index < count) {
                node = GrowthQueue->Remove_Min();
            }
        }
    }
}
