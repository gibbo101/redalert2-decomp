// INIClass::Get_Point (0x0050F670)
// Reads an "x,y" point; defvalue when the entry is missing or empty (the
// text is read through Get_String into a 64-byte buffer).
#include "shared/ini_class.hpp"
#include "shared/unknown_globals.hpp"

INIPoint2D INIClass::Get_Point(char const *section, char const *entry, Point2D const &defvalue) const
{
    char buffer[64];

    if (Get_String(section, entry, unknown_string_83c55c, buffer, sizeof(buffer))) {
        int x, y;
        sscanf(buffer, "%d,%d", &x, &y);
        return INIPoint2D(x, y);
    }
    return (INIPoint2D const &)defvalue;
}
