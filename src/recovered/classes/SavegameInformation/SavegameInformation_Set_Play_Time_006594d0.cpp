// void SavegameInformation::Set_Play_Time(FILETIME const &time) (0x006594D0)
#include "shared/savegame_info.hpp"

void SavegameInformation::Set_Play_Time(FILETIME const &time)
{
    PlayTime = time;
}
