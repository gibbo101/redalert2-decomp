// INIClass::Put_Point (0x0050F990)
// Stores a 3D integer point as "x,y,z".
#include "shared/ini_class.hpp"

bool INIClass::Put_Point(char const *section, char const *entry, INIPoint3D const &value)
{
    char buffer[56];

    sprintf(buffer, "%d,%d,%d", value.X, value.Y, value.Z);
    return Put_String(section, entry, buffer);
}
