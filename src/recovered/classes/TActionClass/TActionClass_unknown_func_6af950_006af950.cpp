// bool TActionClass::unknown_func_6af950(...) (0x006AF950)
// Calls 0x0051FC90 with the cell of waypoint +0x44; always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref ?Unknown_0051FC90@@YGXVCell@@@Z=0051fc90
void __stdcall Unknown_0051FC90(Cell cell);   // 0x0051FC90

bool TActionClass::unknown_func_6af950(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Unknown_0051FC90(unknown_id_source_a3d290->Get_Waypoint_Location(unknown_44));
    return true;
}
