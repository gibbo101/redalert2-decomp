// SavegameInformation::SavegameInformation() (0x00659240)
#include "shared/savegame_info.hpp"

SavegameInformation::SavegameInformation()
{
    unknown_00 = 0;
    unknown_04 = 0;
    unknown_188 = -1;
    unknown_18c = 0;
    GameType = 0;
    Description[0] = 0;
    PlayerName[0] = 0;
    unknown_190[0] = 0;
    unknown_294[0] = 0;
    unknown_2d4[0] = 0;
    StartTime.dwLowDateTime = 0;
    StartTime.dwHighDateTime = 0;
    SaveTime.dwLowDateTime = 0;
    SaveTime.dwHighDateTime = 0;
    PlayTime.dwLowDateTime = 0;
    PlayTime.dwHighDateTime = 0;
}
