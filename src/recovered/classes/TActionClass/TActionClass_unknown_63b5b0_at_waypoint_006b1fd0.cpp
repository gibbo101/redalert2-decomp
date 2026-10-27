// bool TActionClass::unknown_63b5b0_at_waypoint(...) (0x006B1FD0)
// Calls Unknown_0063B5B0(Data, cell of waypoint +0x44); always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref ?Unknown_0063B5B0@@YI_NHVCell@@@Z=0063b5b0
bool __fastcall Unknown_0063B5B0(int kind, Cell cell);   // 0x0063B5B0

bool TActionClass::unknown_63b5b0_at_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Unknown_0063B5B0(Data, unknown_id_source_a3d290->Get_Waypoint_Location(unknown_44));
    return true;
}
