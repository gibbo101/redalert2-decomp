// bool BuildingClass::unknown_slot77(int action, int arg2, int arg3, bool arg4) (0x0043FFE0)
// Action 5 hands the cell (arg2: a Cell pointer) to slot 200 as
// action 1. Action 1: a construction yard of a house failing 0x004F52F0,
// or outside game mode/flag 0x00A3D340, is held back; otherwise a building
// that undeploys or passes slot 153 runs 0x00440140 for the cell. A
// deployable building not held back then queues event 0x16 for itself.
// Always true.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/event.hpp"
#include "shared/target.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref _unknown_game_mode_a3d298=00a3d298
// @ref _unknown_flag_a3d340=00a3d340
// @ref ?unknown_440140@BuildingClass@@QAEXPBVCell@@_N@Z=00440140
// @ref ??0TargetClass@@QAE@PAVAbstractClass@@@Z=006b54a0
// @ref ??0EventClass@@QAE@HHVTargetClass@@@Z=004b5ef0
// @ref ?OutList@@3V?$QueueClass@VEventClass@@$0IA@@@A=00a32338
// @ref __imp__timeGetTime@0=0079a524


bool BuildingClass::unknown_slot77(int action, int arg2, int arg3, bool arg4)
{
    if (action == 5) {
        unknown_slot200(1, &Map[*(Cell const *)arg2], 0, 0);
        return true;
    }
    if (action == 1) {
        bool held = false;
        if (Type->ConstructionYard && (!House->Unknown_004F52F0() || unknown_game_mode_a3d298 == 0 || !unknown_flag_a3d340)) {
            held = true;
        } else if (Type->UndeploysInto != 0 || unknown_slot153()) {
            unknown_440140((Cell const *)arg2, true);
        }
        if (Type->UndeploysInto != 0 && !held) {
            OutList.Add(EventClass(Owner(), 0x16, TargetClass(this)));
        }
    }
    return true;
}
