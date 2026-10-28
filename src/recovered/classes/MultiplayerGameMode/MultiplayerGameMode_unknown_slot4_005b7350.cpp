// bool MultiplayerGameMode::unknown_slot4() -- 0x005B7350
// Slot 4: every player gets a team of its own (team number = list index),
// except players for which 0x0066E290 answers -3 (no team, -1).
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa7c
// @ref ?unknown_66e290@NodeNameType@@QAEHXZ=0066e290

bool MultiplayerGameMode::unknown_slot4()
{
    for (int index = 0; index < unknown_players_a3fa7c.Count(); index++) {
        if (unknown_players_a3fa7c[index]->unknown_66e290() == -3) {
            unknown_players_a3fa7c[index]->Team = -1;
        } else {
            unknown_players_a3fa7c[index]->Team = index;
        }
    }
    return true;
}
