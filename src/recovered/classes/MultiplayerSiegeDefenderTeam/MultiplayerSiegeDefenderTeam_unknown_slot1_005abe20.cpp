// bool MultiplayerSiegeDefenderTeam::unknown_slot1(int player) -- 0x005ABE20
// Slot 1: false when any other player (list index != player) is on the
// defenders' team number 1; true otherwise. Name is a hypothesis.
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUUnknownPlayerEntry@@@@A=00a3fa7c

bool MultiplayerSiegeDefenderTeam::unknown_slot1(int player)
{
    for (int index = 0; index < unknown_players_a3fa7c.Count(); index++) {
        if (player != index && unknown_players_a3fa7c[index]->Team == 1) {
            return false;
        }
    }
    return true;
}
