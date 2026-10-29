// Whether the map allows the game mode named: with no GameModes listed only "standard" is allowed.
bool MultiMission::Unknown_006720E0(Wstring &mode)
{
    if (GameModes.Count() == 0) {
        return mode == "standard";
    }
    for (int index = 0; index < GameModes.Count(); index++) {
        if (mode == GameModes[index]) {
            return true;
        }
    }
    return false;
}
// @ref ??_C@_08GOAK@standard?$AA@=007f3b70
// @ref ??8Wstring@@QBE_NPBD@Z=0076da00
// @ref ??8Wstring@@QBE_NABV0@@Z=0076da70
