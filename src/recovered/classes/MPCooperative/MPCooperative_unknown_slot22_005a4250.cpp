// bool MPCooperative::unknown_slot22() -- 0x005A4250
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/multiplayer_game_mode.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_string.hpp"
// @ref ??_C@_06BILL@Normal?$AA@=007d1b30
// @ref ??_C@_04IOAL@Hard?$AA@=007ceadc
// @ref ??_C@_0BL@JPHD@?$EA?$EA?$EA?$EA?5Adding?5?$CFd?5AI?5players?6?$AA@=007e35f0
// @ref ??_C@_0BM@IBMO@?$EA?$EA?$EA?$EA?5?5?5?5?5AI?5difficulty?3?5?$CFd?6?$AA@=007e35b4
// @ref ??_C@_0BN@HBMM@?$EA?$EA?$EA?$EA?5Setting?5slot?5?$CFd?5for?5AI?6?$AA@=007e35d0
// @ref ?Unknown_005c6600@@YIHH@Z=005c6600

bool MPCooperative::unknown_slot22()
{
    int players = Unknown_005c6600(unknown_session_a3d298.ScenarioIndex) - 2;
    Debug_Printf("@@@@ Adding %d AI players\n", players);
    if (players <= 0) {
        return false;
    }
    int added = 0;
    unknown_session_a3d298.AICount = players;
    UnknownDescriptionRecord_00490E00 *record;
    unknown_campaigns_40->Get_Record_00490C50(unknown_340, &record);
    if (record == 0) {
        return false;
    }
    if (record->Enemies.Count() == 0) {
        return false;
    }
    for (int slot = 2; slot < 8; slot++) {
        if (added < players) {
            Debug_Printf("@@@@ Setting slot %d for AI\n", slot);
            char *name = record->AIName;
            if (strcmp(name, "Normal") == 0) {
                unknown_session_a3d298.AIDifficulty[slot] = 1;
            } else if (strcmp(name, "Hard") == 0) {
                unknown_session_a3d298.AIDifficulty[slot] = 0;
            } else {
                unknown_session_a3d298.AIDifficulty[slot] = 2;
            }
            Debug_Printf("@@@@     AI difficulty: %d\n", unknown_session_a3d298.AIDifficulty[slot]);
            unknown_session_a3d298.AICountry[slot] = -2;
            unknown_session_a3d298.AIColor[slot] = -2;
            added++;
        } else {
            unknown_session_a3d298.AIDifficulty[slot] = -1;
            unknown_session_a3d298.AICountry[slot] = -1;
            unknown_session_a3d298.AIColor[slot] = -1;
        }
    }
    return true;
}
