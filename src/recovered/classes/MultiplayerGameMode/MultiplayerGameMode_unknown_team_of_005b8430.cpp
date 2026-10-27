// int MultiplayerGameMode::unknown_team_of_5b8430(int id) -- 0x005B8430
// The team number of the player with identifier `id` (+0x5F), or -1.

int MultiplayerGameMode::unknown_team_of_5b8430(int id)
{
    for (int index = 0; index < unknown_players_a3fa7c.Count(); index++) {
        if (unknown_players_a3fa7c[index]->unknown_5f == id) {
            return unknown_players_a3fa7c[index]->Team;
        }
    }
    return -1;
}
