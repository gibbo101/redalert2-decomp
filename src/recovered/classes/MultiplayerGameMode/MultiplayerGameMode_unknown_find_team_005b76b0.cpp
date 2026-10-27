// MultiplayerTeam *MultiplayerGameMode::unknown_find_team_5b76b0(int number) -- 0x005B76B0
// The team with a number; the teams are (re)created through slot 41 first
// when fewer than three exist.

MultiplayerTeam *MultiplayerGameMode::unknown_find_team_5b76b0(int number)
{
    if (Teams.Count() < 3) {
        for (int index = 0; index < Teams.Count(); index++) {
            delete Teams[index];
        }
        Teams.Clear();
        unknown_slot41(&Teams);
    }
    for (int index = 0; index < Teams.Count(); index++) {
        MultiplayerTeam *team = Teams[index];
        if (team != 0 && team->Number == number) {
            return team;
        }
    }
    return 0;
}
