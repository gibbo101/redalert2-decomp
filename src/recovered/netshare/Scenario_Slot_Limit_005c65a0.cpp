// int __fastcall Scenario_Slot_Limit_005c65a0(int scenario) (0x005C65A0)
#include "shared/lobby.hpp"
// @ref ?Unknown_005c6600@@YIHH@Z=005c6600

int __fastcall Scenario_Slot_Limit_005c65a0(int scenario)
{
    if (scenario == -1) {
        return 8;
    }
    int limit = Unknown_005c6600(scenario);
    if (unknown_session_a3d29c != 0) {
        int mode_limit = unknown_session_a3d29c->unknown_slot32();
        if (mode_limit != -1 && mode_limit < limit) {
            limit = mode_limit;
        }
    }
    if (unknown_game_mode_a3d298 == 4) {
        if (unknown_73c3a0()) {
            limit &= ~1;
        } else if (unknown_73c370()) {
            limit = 2;
        }
    }
    return limit;
}
