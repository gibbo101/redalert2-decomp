// INIClass::Get_Entry (0x0050CE00)
// Key of the index'th entry (in file order) of the named section, or null
// when the section is missing or index is past its last entry.
#include "shared/ini_class.hpp"

char const *INIClass::Get_Entry(char const *section, int index) const
{
    INISection *secptr = Find_Section(section);
    if (secptr != 0 && index < secptr->EntryIndex.Count()) {
        INIEntry *entptr = secptr->EntryList.First();
        while (entptr != 0 && entptr->Is_Valid()) {
            if (index == 0) {
                return entptr->Key;
            }
            index--;
            entptr = entptr->Next();
        }
    }
    return 0;
}
