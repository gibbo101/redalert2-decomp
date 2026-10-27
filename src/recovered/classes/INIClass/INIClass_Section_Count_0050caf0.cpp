// INIClass::Section_Count (0x0050CAF0)
// Number of sections.
#include "shared/ini_class.hpp"

int INIClass::Section_Count() const
{
    return SectionIndex.Count();
}
