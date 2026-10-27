// INIClass::Find_Section (0x0050C9B0)
// Returns the section with this name, or null (also for a null name).
#include "shared/ini_class.hpp"

INIClass::INISection *INIClass::Find_Section(char const *section) const
{
    if (section != 0) {
        long crc = CRCEngine()(section, strlen(section));
        if (SectionIndex.Is_Present(crc)) {
            return SectionIndex[crc];
        }
    }
    return 0;
}
