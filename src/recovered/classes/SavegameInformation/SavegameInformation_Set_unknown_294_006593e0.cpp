// void SavegameInformation::Set_unknown_294(char const *text) (0x006593E0)
#include "shared/savegame_info.hpp"

void SavegameInformation::Set_unknown_294(char const *text)
{
    unknown_294[0x3F] = 0;
    strncpy(unknown_294, text, 0x3F);
}
