// MultiplayerGameMode::~MultiplayerGameMode() -- 0x005B6E20
// Deletes the teams (virtually) and the INI object, then the members.
// @ref ??1WideString@@QAE@XZ=0076fa50
// @ref ??1Wstring@@QAE@XZ=0076d9e0
// @ref ??_7MultiplayerGameMode@@6B@=007a71b8
// @ref ??_7?$VectorClass@PAVMultiplayerTeam@@@@6B@=007a7290

MultiplayerGameMode::~MultiplayerGameMode()
{
    for (int index = 0; index < Teams.Count(); index++) {
        delete Teams[index];
    }
    Teams.Clear();
    delete unknown_ini_38;
}
