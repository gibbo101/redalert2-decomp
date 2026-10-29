bool UnknownSessionState::Am_I_Master(HouseClass *house)
{
    if (house == 0) {
        house = unknown_player_a35db4;
    }
    if (unknown_game_mode_a3d298 == 4 && house != 0) {
        if (MasterPlayerID != -1) {
            return house->ArrayIndex == MasterPlayerID;
        }
        if (_wcsicmp(house->UIName, MasterPlayerName) == 0) {
            return true;
        }
    }
    for (int i = 0; i < Houses.Count(); i++) {
        HouseClass *player = Houses[i];
        if (player->unknown_134 && !player->unknown_13d) {
            if (house == player) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}
