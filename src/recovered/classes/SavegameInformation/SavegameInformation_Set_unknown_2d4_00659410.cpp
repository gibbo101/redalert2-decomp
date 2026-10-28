// void SavegameInformation::Set_unknown_2d4(char const *text) (0x00659410)
#include "shared/savegame_info.hpp"

void SavegameInformation::Set_unknown_2d4(char const *text)
{
    unknown_2d4[0x103] = 0;
    strncpy(unknown_2d4, text, 0x103);
}
