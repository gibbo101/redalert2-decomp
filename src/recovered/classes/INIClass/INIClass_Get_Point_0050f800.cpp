// INIClass::Get_Point (0x0050F800)
// Wstring overload of Get_Point.
#include "shared/ini_class.hpp"

INIPoint2D INIClass::Get_Point(Wstring const &section, Wstring const &entry, Point2D const &defvalue) const
{
    return Get_Point(section.Peek_Buffer(), entry.Peek_Buffer(), defvalue);
}
