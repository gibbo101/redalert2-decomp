// void TiberiumClass::Init_Growth_Queue() (0x006EA540)
// Drops this type's growth queue and tables, allocates them for the current map (one entry and one
// flag per cell) and refills them. Init_Growth expands it (this copy is never called).
#include "shared/tiberium.hpp"
#include "shared/veinhole.hpp"
// @ref ?unknown_cells_428ac0@@YAHXZ=00428ac0
// @ref ?Rebuild_Growth@TiberiumClass@@QAEXXZ=006ea680

void TiberiumClass::Init_Growth_Queue()
{
    if (GrowthQueue != 0) {
        GrowthQueue->Clear();
        delete GrowthQueue;
        GrowthQueue = 0;
    }
    if (GrowthData != 0) {
        delete[] GrowthData;
        GrowthData = 0;
    }
    if (GrowthMap != 0) {
        delete[] GrowthMap;
        GrowthMap = 0;
    }
    GrowthCount = 0;
    GrowthData = new UnknownVeinNode[unknown_cells_428ac0()];
    GrowthMap = new bool[unknown_cells_428ac0()];
    GrowthQueue = new UnknownVeinHeap(unknown_cells_428ac0());
    Rebuild_Growth();
}
