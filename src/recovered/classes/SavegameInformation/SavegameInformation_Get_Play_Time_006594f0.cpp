// void SavegameInformation::Get_Play_Time(FILETIME &time) const (0x006594F0)
#include "shared/savegame_info.hpp"

void SavegameInformation::Get_Play_Time(FILETIME &time) const
{
    time = PlayTime;
}
