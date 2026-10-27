// bool BuildingClass::unknown_445ab0() (0x00445AB0)
// False unless the type undeploys into a unit. True for a SensorArray,
// TickTank, ICBMLauncher or Artillary type; otherwise (only in a game mode)
// when unknown_1b0 is set and the owner's 0x004F52F0 holds, in single-player
// or with the flag at 0x00A3D340.
#include "shared/building.hpp"
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_flag_a3d340@@3_NA=00a3d340

bool BuildingClass::unknown_445ab0()
{
    BuildingTypeClass *type = Type;
    if (!type->UndeploysInto) {
        return false;
    }
    if (type->SensorArray || type->TickTank || type->ICBMLauncher || type->Artillary) {
        return true;
    }
    if (!unknown_game_mode_a3d298) {
        return false;
    }
    if (unknown_1b0 && House->Unknown_004F52F0() && (!unknown_game_mode_a3d298 || unknown_flag_a3d340)) {
        return true;
    }
    return false;
}
