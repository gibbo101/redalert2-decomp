// bool TechnoClass::unknown_slot199(int type) (0x006CC510, slot 199)
// Queues an event of the given type about this object for the player's
// house; planning mode refuses it instead.
#include "shared/techno.hpp"
#include "shared/event.hpp"
#include "shared/target.hpp"
#include "shared/planning.hpp"
// @ref ??0TargetClass@@QAE@PAVAbstractClass@@@Z=006b54a0
// @ref ??0EventClass@@QAE@HHVTargetClass@@@Z=004b5ef0
// @ref ?OutList@@3V?$QueueClass@VEventClass@@$0IA@@@A=00a32338
// @ref __imp__timeGetTime@0=0079a524
// @ref ?Planning_Active@@YA_NXZ=00614840
// @ref ?Planning_Refuse_Event@@YIXPBVEventClass@@@Z=00616d70
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4

bool Planning_Active();

bool TechnoClass::unknown_slot199(int type)
{
    EventClass event(unknown_player_a35db4->ArrayIndex, type, TargetClass(this));
    if (Planning_Active()) {
        Planning_Refuse_Event(&event);
        return false;
    }
    OutList.Add(event);
    return true;
}
