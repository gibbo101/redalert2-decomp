// void SavegameInformation::Set_Description(wchar_t const *text) (0x006592F0)
#include "shared/savegame_info.hpp"

void SavegameInformation::Set_Description(wchar_t const *text)
{
    Description[0x7F] = 0;
    wcsncpy(Description, text, 0x7F);
}
