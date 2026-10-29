// The lobby slot whose name equals the text; 0 when none.
int UnknownSessionState::Unknown_00672FF0(char const *name)
{
    for (int slot = 0; slot < 8; slot++) {
        if (_stricmp(name, Unknown_006FA120(unknown_player_slots_a3fa98[slot]->Name)) == 0) {
            return slot;
        }
    }
    return 0;
}
// @ref ?unknown_player_slots_a3fa98@@3PAPAUNodeNameType@@A=00a3fa98
// @ref ?Unknown_006FA120@@YIPADPBG@Z=006fa120
// @ref __stricmp=00781f20
