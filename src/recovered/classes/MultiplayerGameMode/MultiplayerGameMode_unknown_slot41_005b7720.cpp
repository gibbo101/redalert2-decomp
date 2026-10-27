// void MultiplayerGameMode::unknown_slot41(DynamicVectorClass<MultiplayerTeam *> *teams) -- 0x005B7720
// Slot 41: the default teams: the observers' team, then one battle team per
// team number 1..the team count (0x00A3D558) (0x005A2550).
// @ref ??0MultiplayerObserverTeam@@QAE@XZ=005aa7b0
// @ref ?unknown_create_battle_team_005a2550@@YIPAVMultiplayerTeam@@H@Z=005a2550
// @ref ?unknown_team_count_a3d558@@3HA=00a3d558

extern int unknown_team_count_a3d558;
MultiplayerTeam *__fastcall unknown_create_battle_team_005a2550(int number);

void MultiplayerGameMode::unknown_slot41(DynamicVectorClass<MultiplayerTeam *> *teams)
{
    teams->Add(new MultiplayerObserverTeam);
    for (int number = 1; number <= unknown_team_count_a3d558; number++) {
        teams->Add(unknown_create_battle_team_005a2550(number));
    }
}
