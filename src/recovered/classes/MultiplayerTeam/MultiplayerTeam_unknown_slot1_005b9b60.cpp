// bool MultiplayerTeam::unknown_slot1(int player) -- 0x005B9B60
// Slot 1: true for a valid index into the player list (0x00A3FA7C).

bool MultiplayerTeam::unknown_slot1(int player)
{
    if (player < 0 || player >= unknown_players_a3fa7c.Count()) {
        return false;
    }
    return true;
}
