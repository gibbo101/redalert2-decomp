// void TiberiumClass::Init_Spread_Queue() (0x006E9A50)
// Drops this type's spread queue and tables, allocates them for the current map (one entry and one
// flag per cell) and refills them. Init_Spread expands it (this copy is never called).
#include "shared/tiberium.hpp"
#include "shared/veinhole.hpp"
// @ref ?unknown_cells_428ac0@@YAHXZ=00428ac0
// @ref ?Rebuild_Spread@TiberiumClass@@QAEXXZ=006e9b90

void TiberiumClass::Init_Spread_Queue()
{
    if (SpreadQueue != 0) {
        SpreadQueue->Clear();
        delete SpreadQueue;
        SpreadQueue = 0;
    }
    if (SpreadData != 0) {
        delete[] SpreadData;
        SpreadData = 0;
    }
    if (SpreadMap != 0) {
        delete[] SpreadMap;
        SpreadMap = 0;
    }
    SpreadCount = 0;
    SpreadData = new MapSurfaceData[unknown_cells_428ac0()];
    SpreadMap = new bool[unknown_cells_428ac0()];
    SpreadQueue = new PriorityQueueClass<MapSurfaceData>(unknown_cells_428ac0());
    Rebuild_Spread();
}
