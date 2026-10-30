// INIClass::Get_Vector (0x0050FE60)
// Reads a "x,y,z" float triple; defvalue when the entry is missing or empty
// (the text is read through Get_String into a 64-byte buffer).
#include "shared/ini_class.hpp"
#include "shared/unknown_globals.hpp"

INIVector3 INIClass::Get_Vector(char const *section, char const *entry, INIVector3 const &defvalue) const
{
    char buffer[64];

    if (Get_String(section, entry, unknown_string_83c55c, buffer, sizeof(buffer)) != 0) {
        float x, y, z;
        sscanf(buffer, "%f,%f,%f", &x, &y, &z);
        return INIVector3(x, y, z);
    }
    return defvalue;
}
