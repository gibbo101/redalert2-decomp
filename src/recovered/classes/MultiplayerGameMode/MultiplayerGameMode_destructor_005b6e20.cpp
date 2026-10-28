// MultiplayerGameMode::~MultiplayerGameMode() -- 0x005B6E20
// Deletes the teams (virtually, unknown_clear_teams_5b77e0 expanded) and the
// INI object, then the members.
// @ref ??1WideString@@QAE@XZ=0076fa50
// @ref ??1Wstring@@QAE@XZ=0076d9e0
// @ref ??_7MultiplayerGameMode@@6B@=007a71b8
// @ref ??_7?$VectorClass@PAVMultiplayerTeam@@@@6B@=007a7290

MultiplayerGameMode::~MultiplayerGameMode()
{
    unknown_clear_teams_5b77e0();
    delete unknown_ini_38;
}
