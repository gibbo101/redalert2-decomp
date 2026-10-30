// INIClass::Get_Point (0x0050FA40)
// Reads a "x,y,z" integer point; defvalue when the entry is missing or empty
// (the text is read through Get_String into a 64-byte buffer).
#include "shared/ini_class.hpp"
#include "shared/unknown_globals.hpp"

INIPoint3D INIClass::Get_Point(char const *section, char const *entry, INIPoint3D const &defvalue) const
{
    char buffer[64];

    if (Get_String(section, entry, unknown_string_83c55c, buffer, sizeof(buffer)) != 0) {
        int x, y, z;
        sscanf(buffer, "%d,%d,%d", &x, &y, &z);
        return INIPoint3D(x, y, z);
    }
    return defvalue;
}
