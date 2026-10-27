// INIClass::Get_Int (0x0050D7F0)
// Reads an integer entry. "$1F" and "1Fh" are hexadecimal, anything else is
// decimal (atoi). Returns defvalue when the section, entry or value is
// missing.
#include "shared/ini_class.hpp"

int INIClass::Get_Int(char const *section, char const *entry, int defvalue) const
{
    if (section == 0 || entry == 0) {
        return defvalue;
    }

    INIEntry *entptr = Find_Entry(section, entry);
    if (entptr != 0 && entptr->Value != 0) {
        if (*entptr->Value == '$') {
            sscanf(entptr->Value, "$%x", &defvalue);
        } else if (tolower(entptr->Value[strlen(entptr->Value) - 1]) == 'h') {
            sscanf(entptr->Value, "%xh", &defvalue);
        } else {
            defvalue = atoi(entptr->Value);
        }
    }
    return defvalue;
}
