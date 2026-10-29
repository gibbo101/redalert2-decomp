#include "shared/crt_string.hpp"
#include "shared/session_state.hpp"
// The lobby slot whose name equals this session player's name; 0 when none.
int UnknownSessionState::Unknown_00672F90(int player)
{
    for (int slot = 0; slot < 8; slot++) {
        NodeNameType *entry = unknown_player_slots_a3fa98[slot];
        char *name = Unknown_006FA120(unknown_players_a3fa7c[player]->Name);
        if (_stricmp(name, Unknown_006FA120(entry->Name)) == 0) {
            return slot;
        }
    }
    return 0;
}
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa7c
// @ref ?unknown_player_slots_a3fa98@@3PAPAUNodeNameType@@A=00a3fa98
// @ref ?Unknown_006FA120@@YIPADPBG@Z=006fa120
// @ref __stricmp=00781f20
