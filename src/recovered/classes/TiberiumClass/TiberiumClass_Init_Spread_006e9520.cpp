// void TiberiumClass::Init_Spread() (0x006E9520)
// Rebuilds the spread queue of every tiberium type for the current map (Init_Spread_Queue's body, written
// out: the original expands that member here and keeps its unreferenced copy after this function).
#include "shared/tiberium.hpp"
#include "shared/veinhole.hpp"
// @ref ?unknown_cells_428ac0@@YAHXZ=00428ac0
// @ref ?Rebuild_Spread@TiberiumClass@@QAEXXZ=006e9b90

void TiberiumClass::Init_Spread()
{
    for (int index = 0; index < unknown_TiberiumClass_list_00ac0b30.Count(); index++) {
        TiberiumClass *tiberium = unknown_TiberiumClass_list_00ac0b30[index];
        if (tiberium->SpreadQueue != 0) {
            tiberium->SpreadQueue->Clear();
            delete tiberium->SpreadQueue;
            tiberium->SpreadQueue = 0;
        }
        if (tiberium->SpreadData != 0) {
            delete[] tiberium->SpreadData;
            tiberium->SpreadData = 0;
        }
        if (tiberium->SpreadMap != 0) {
            delete[] tiberium->SpreadMap;
            tiberium->SpreadMap = 0;
        }
        tiberium->SpreadCount = 0;
        tiberium->SpreadData = new UnknownVeinNode[unknown_cells_428ac0()];
        tiberium->SpreadMap = new bool[unknown_cells_428ac0()];
        tiberium->SpreadQueue = new UnknownVeinHeap(unknown_cells_428ac0());
        tiberium->Rebuild_Spread();
    }
}
