// void SavegameInformation::Get_Start_Time(FILETIME &time) const (0x00659470)
#include "shared/savegame_info.hpp"

void SavegameInformation::Get_Start_Time(FILETIME &time) const
{
    time = StartTime;
}
