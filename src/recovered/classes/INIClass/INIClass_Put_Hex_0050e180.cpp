// INIClass::Put_Hex (0x0050E180)
// Stores an integer as unprefixed upper-case hex ("1F").
#include "shared/ini_class.hpp"

bool INIClass::Put_Hex(char const *section, char const *entry, int number)
{
    char buffer[512];

    sprintf(buffer, "%X", number);
    return Put_String(section, entry, buffer);
}
