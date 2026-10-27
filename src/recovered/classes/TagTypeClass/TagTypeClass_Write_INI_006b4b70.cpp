// bool TagTypeClass::Write_INI(CCINIClass &ini) const (0x006B4B70)
#include "shared/object.hpp"

bool TagTypeClass::Write_INI(CCINIClass &ini) const
{
    char buffer[128];
    if (Triggers == 0) {
        wsprintfA(buffer, "%s,<none>", (char const *)Name);
        ini.Put_String(unknown_tags_section_7ac770, ID, buffer);
    } else {
        wsprintfA(buffer, "%d,%s,%s", Persistence, (char const *)Name, (char const *)Triggers->ID);
        ini.Put_String(unknown_tags_section_7ac770, ID, buffer);
    }
    return true;
}
