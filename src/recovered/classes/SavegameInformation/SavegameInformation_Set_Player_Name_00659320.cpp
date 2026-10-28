// void SavegameInformation::Set_Player_Name(wchar_t const *text) (0x00659320)
#include "shared/savegame_info.hpp"

void SavegameInformation::Set_Player_Name(wchar_t const *text)
{
    PlayerName[0x3F] = 0;
    wcsncpy(PlayerName, text, 0x3F);
}
