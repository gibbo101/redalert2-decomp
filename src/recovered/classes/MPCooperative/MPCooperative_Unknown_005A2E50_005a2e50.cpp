// int MPCooperative::Unknown_005A2E50() -- 0x005A2E50
// The last campaign record whose first map entry lists the session's multiplayer map, or -1.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
// @ref __strnicmp=007858d0
#include "shared/multiplayer_game_mode.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/session_state.hpp"
#include "shared/multi_mission.hpp"
#include "shared/crt_tokens.hpp"

int MPCooperative::Unknown_005A2E50()
{
    if (unknown_campaigns_40 == 0) {
        return -1;
    }
    int found = -1;
    for (int i = 0; i < unknown_campaigns_40->Count; i++) {
        UnknownDescriptionRecord_00490E00 *record;
        unknown_campaigns_40->Get_Record_00490C50(i, &record);
        for (int m = 0; m < 3; m++) {
            if (unknown_session_a3d298.ScenarioIndex != 0) {
                char const *scenario = unknown_multi_missions_a3d8d8[unknown_session_a3d298.ScenarioIndex]->unknown_58;
                if (_strnicmp(scenario, record->Maps + m * 260, strlen(record->Maps + m * 260)) == 0) {
                    found = i;
                }
            }
        }
    }
    return found;
}
// @ref ??_EWstring@@QAEPAXI@Z=0040af40
