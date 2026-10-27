// bool BuildingClass::unknown_slot39() (0x0044A930, slot 39)
// False while +0x3FC is positive; true when slot 153 holds; otherwise
// whether the type undeploys into a unit, which for type flag +0x1353 also
// needs game mode, the flag at 0x00A3D340 and the owner's 0x004F52F0.
#include "shared/building.hpp"
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_flag_a3d340@@3_NA=00a3d340

bool BuildingClass::unknown_slot39()
{
    if (unknown_3fc > 0) {
        return false;
    }
    if (unknown_slot153()) {
        return true;
    }
    if (Type->ConstructionYard) {
        if (!unknown_game_mode_a3d298 || !unknown_flag_a3d340 || !House->Unknown_004F52F0()) {
            return false;
        }
    }
    return Type->UndeploysInto != 0;
}
