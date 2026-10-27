// INIClass::Get_Hex (0x0050E230)
// Reads an entry as unprefixed hexadecimal ("%x"); defvalue when the
// section, entry or value is missing.
#include "shared/ini_class.hpp"

int INIClass::Get_Hex(char const *section, char const *entry, int defvalue) const
{
    if (section == 0 || entry == 0) {
        return defvalue;
    }

    INIEntry *entptr = Find_Entry(section, entry);
    if (entptr != 0 && entptr->Value != 0) {
        sscanf(entptr->Value, "%x", &defvalue);
    }
    return defvalue;
}
