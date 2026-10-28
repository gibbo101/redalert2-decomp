// void TiberiumClass::Init_Growth() (0x006E9FE0)
// Rebuilds the growth queue of every tiberium type for the current map (Init_Growth_Queue's body, written
// out: the original expands that member here and keeps its unreferenced copy after this function).
#include "shared/tiberium.hpp"
#include "shared/veinhole.hpp"
// @ref ?unknown_cells_428ac0@@YAHXZ=00428ac0
// @ref ?Rebuild_Growth@TiberiumClass@@QAEXXZ=006ea680

void TiberiumClass::Init_Growth()
{
    for (int index = 0; index < unknown_TiberiumClass_list_00ac0b30.Count(); index++) {
        TiberiumClass *tiberium = unknown_TiberiumClass_list_00ac0b30[index];
        if (tiberium->GrowthQueue != 0) {
            tiberium->GrowthQueue->Clear();
            delete tiberium->GrowthQueue;
            tiberium->GrowthQueue = 0;
        }
        if (tiberium->GrowthData != 0) {
            delete[] tiberium->GrowthData;
            tiberium->GrowthData = 0;
        }
        if (tiberium->GrowthMap != 0) {
            delete[] tiberium->GrowthMap;
            tiberium->GrowthMap = 0;
        }
        tiberium->GrowthCount = 0;
        tiberium->GrowthData = new UnknownVeinNode[unknown_cells_428ac0()];
        tiberium->GrowthMap = new bool[unknown_cells_428ac0()];
        tiberium->GrowthQueue = new UnknownVeinHeap(unknown_cells_428ac0());
        tiberium->Rebuild_Growth();
    }
}
