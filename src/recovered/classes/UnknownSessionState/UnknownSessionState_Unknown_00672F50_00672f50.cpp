// The unknown_3022 value of the session player with this ID; 0 when none has it.
unsigned short UnknownSessionState::Unknown_00672F50(int id)
{
    for (int index = 0; index < unknown_players_a3fa7c.Count(); index++) {
        if (unknown_players_a3fa7c[index]->ID == id) {
            return unknown_3022.unknown[index];
        }
    }
    return 0;
}
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa7c
