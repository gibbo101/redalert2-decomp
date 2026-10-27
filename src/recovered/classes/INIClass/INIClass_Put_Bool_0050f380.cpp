// INIClass::Put_Bool (0x0050F380)
// Stores a flag as "yes" or "no".
#include "shared/ini_class.hpp"

bool INIClass::Put_Bool(char const *section, char const *entry, bool value)
{
    if (value) {
        return Put_String(section, entry, "yes");
    }
    return Put_String(section, entry, "no");
}
