// SavegameInformation::SavegameInformation() (0x00659240)
// The first function of the SavegameInformation unit (TibSun savever.cpp, a separate file from
// saveload.cpp: SaveLoad's Save_Game/Load_Game call its accessors out of line). The unit's smart
// pointers release through comip's _Release, expanded inline (shared/com_ptr.hpp).
#define COM_PTR_IMPLEMENT_RELEASE
#define COM_PTR_RELEASE_IN_DESTRUCTOR
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
