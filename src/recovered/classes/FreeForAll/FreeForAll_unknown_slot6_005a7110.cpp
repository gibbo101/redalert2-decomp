// bool FreeForAll::unknown_slot6() -- 0x005A7110
// Slot 6: like slot 5 after the base slot 6 (0x005B73D0).
// @ref ?unknown_slot6@MultiplayerGameMode@@UAE_NXZ=005b73d0
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUUnknownPlayerEntry@@@@A=00a3fa7c

bool FreeForAll::unknown_slot6()
{
    if (!MultiplayerGameMode::unknown_slot6()) {
        return false;
    }
    for (int index = 0; index < unknown_players_a3fa7c.Count(); index++) {
        if (unknown_players_a3fa7c[index]->Team != -1) {
            unknown_players_a3fa7c[index]->Team = index;
        }
    }
    return true;
}
