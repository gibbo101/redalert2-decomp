// void SavegameInformation::Set_Start_Time(FILETIME const &time) (0x00659450)
#include "shared/savegame_info.hpp"

void SavegameInformation::Set_Start_Time(FILETIME const &time)
{
    StartTime = time;
}
