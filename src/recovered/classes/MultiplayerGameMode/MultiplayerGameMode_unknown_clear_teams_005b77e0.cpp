// void MultiplayerGameMode::unknown_clear_teams_5b77e0() -- 0x005B77E0
// Deletes every team and empties the list.

void MultiplayerGameMode::unknown_clear_teams_5b77e0()
{
    for (int index = 0; index < Teams.Count(); index++) {
        delete Teams[index];
    }
    Teams.Clear();
}
