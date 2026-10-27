// bool MultiplayerTeam::unknown_slot2(int player) -- 0x005B9B80
// Slot 2: puts a valid player (virtual slot 1) on this team.

bool MultiplayerTeam::unknown_slot2(int player)
{
    if (!unknown_slot1(player)) {
        return false;
    }
    unknown_players_a3fa7c[player]->Team = Number;
    return true;
}
