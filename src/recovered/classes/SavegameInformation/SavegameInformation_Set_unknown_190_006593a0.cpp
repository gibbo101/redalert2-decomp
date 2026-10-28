// void SavegameInformation::Set_unknown_190(char const *text) (0x006593A0)
#include "shared/savegame_info.hpp"

void SavegameInformation::Set_unknown_190(char const *text)
{
    unknown_190[0x103] = 0;
    strncpy(unknown_190, text, 0x103);
}
