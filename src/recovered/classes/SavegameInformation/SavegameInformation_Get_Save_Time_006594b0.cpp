// void SavegameInformation::Get_Save_Time(FILETIME &time) const (0x006594B0)
#include "shared/savegame_info.hpp"

void SavegameInformation::Get_Save_Time(FILETIME &time) const
{
    time = SaveTime;
}
