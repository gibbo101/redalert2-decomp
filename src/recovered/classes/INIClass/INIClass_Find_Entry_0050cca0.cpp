// INIClass::Find_Entry (0x0050CCA0)
// Returns the entry with this key in the named section, or null.
#include "shared/ini_class.hpp"

INIClass::INIEntry *INIClass::Find_Entry(char const *section, char const *entry) const
{
    INISection *secptr = Find_Section(section);
    if (secptr != 0) {
        return secptr->Find_Entry(entry);
    }
    return 0;
}
