// INIClass::Put_Time (0x00510610)
// Stores a duration given in 1/60 s ticks as "hh:mm:ss". The name is a
// hypothesis; the unit follows from the three divisions by 60.
#include "shared/ini_class.hpp"

bool INIClass::Put_Time(char const *section, char const *entry, int ticks)
{
    char buffer[32];

    int seconds = ticks / 60;
    int minutes = seconds / 60;
    int hours = minutes / 60;
    sprintf(buffer, "%02d:%02d:%02d", hours, minutes - hours * 60, seconds - minutes * 60);
    return Put_String(section, entry, buffer);
}
