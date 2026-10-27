// INIClass::Get_Bool (0x0050F410)
// Reads a flag from the first character of the value: Y, T or 1 is true,
// N, F or 0 is false (case-insensitive); anything else, or a missing
// section/entry/value, gives defvalue.
#include "shared/ini_class.hpp"

bool INIClass::Get_Bool(char const *section, char const *entry, bool defvalue) const
{
    if (section == 0 || entry == 0) {
        return defvalue;
    }

    INIEntry *entptr = Find_Entry(section, entry);
    if (entptr != 0 && entptr->Value != 0) {
        switch (toupper(*entptr->Value)) {
            case 'Y':
            case 'T':
            case '1':
                return true;

            case 'N':
            case 'F':
            case '0':
                return false;
        }
    }
    return defvalue;
}
