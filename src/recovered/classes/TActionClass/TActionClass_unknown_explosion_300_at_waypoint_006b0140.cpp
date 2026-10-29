// bool TActionClass::unknown_explosion_300_at_waypoint(...) (0x006B0140)
// Explosion effects of 300 with the rules warhead at +0xC74 at the coordinate of waypoint Data; always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/rules.hpp"
#include "shared/anim.hpp"
// @ref ?Waypoint_Coord@UnknownIDSource@@QBE?AUCoordStruct@@H@Z=006631c0
// @ref ?Unknown_0047F600@@YIXUCoordStruct@@HPAVWarheadTypeClass@@HH@Z=0047f600
// @ref ?Rules@@3PAVRulesClass@@A=00839848

bool TActionClass::unknown_explosion_300_at_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Unknown_0047F600(unknown_id_source_a3d290->Waypoint_Coord(Data), 300, Rules->unknown_c74, 0, 0);
    return true;
}
