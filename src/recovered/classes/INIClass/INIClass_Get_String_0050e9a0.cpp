// INIClass::Get_String (0x0050E9A0)
// Copies the entry's value (or defvalue when the entry is missing) into
// buffer, truncated to size - 1 characters and trimmed, and returns its
// length. With no value and no default the buffer becomes empty. Returns 0
// for a null section/entry/buffer or a size below 2.
#include "shared/ini_class.hpp"

int INIClass::Get_String(char const *section, char const *entry, char const *defvalue, char *buffer, int size) const
{
    if (buffer == 0 || size < 2 || section == 0 || entry == 0) {
        return 0;
    }

    INIEntry *entptr = Find_Entry(section, entry);
    if (entptr != 0 && entptr->Value != 0) {
        defvalue = entptr->Value;
    }

    if (defvalue == 0) {
        buffer[0] = '\0';
        return 0;
    }
    strncpy(buffer, defvalue, size);
    buffer[size - 1] = '\0';
    strtrim(buffer);
    return strlen(buffer);
}
