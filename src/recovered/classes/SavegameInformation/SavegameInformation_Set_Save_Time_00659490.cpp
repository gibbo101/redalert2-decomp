// void SavegameInformation::Set_Save_Time(FILETIME const &time) (0x00659490)
#include "shared/savegame_info.hpp"

void SavegameInformation::Set_Save_Time(FILETIME const &time)
{
    SaveTime = time;
}
