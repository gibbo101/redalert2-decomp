// INIClass::Put_Point (0x0050F5D0)
// Stores a 2D point as "x,y".
#include "shared/ini_class.hpp"

bool INIClass::Put_Point(char const *section, char const *entry, INIPoint2D const &value)
{
    char buffer[56];

    sprintf(buffer, "%d,%d", value.X, value.Y);
    return Put_String(section, entry, buffer);
}
