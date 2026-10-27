// INIClass::Entry_Count (0x0050CB00)
// Number of entries in the named section; 0 when the section is missing.
#include "shared/ini_class.hpp"

int INIClass::Entry_Count(char const *section) const
{
    INISection *secptr = Find_Section(section);
    if (secptr != 0) {
        return secptr->EntryIndex.Count();
    }
    return 0;
}
