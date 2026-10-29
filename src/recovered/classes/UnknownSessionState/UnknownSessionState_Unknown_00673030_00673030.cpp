// The session player whose name equals this lobby slot's name; 0 when none.
int UnknownSessionState::Unknown_00673030(int slot)
{
    for (int index = 0; index < unknown_players_a3fa7c.Count(); index++) {
        NodeNameType *entry = unknown_player_slots_a3fa98[slot];
        char *name = Unknown_006FA120(unknown_players_a3fa7c[index]->Name);
        if (_stricmp(name, Unknown_006FA120(entry->Name)) == 0) {
            return index;
        }
    }
    return 0;
}
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa7c
// @ref ?unknown_player_slots_a3fa98@@3PAPAUNodeNameType@@A=00a3fa98
// @ref ?Unknown_006FA120@@YIPADPBG@Z=006fa120
// @ref __stricmp=00781f20
