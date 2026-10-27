// INIClass::Put_Vector (0x0050FD90)
// Stores three floats as "x,y,z" ("%f" each).
#include "shared/ini_class.hpp"

bool INIClass::Put_Vector(char const *section, char const *entry, INIVector3 const &value)
{
    char buffer[56];

    sprintf(buffer, "%f,%f,%f", value.X, value.Y, value.Z);
    return Put_String(section, entry, buffer);
}
