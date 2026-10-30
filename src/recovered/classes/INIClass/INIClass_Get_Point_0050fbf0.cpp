// INIClass::Get_Point (0x0050FBF0)
// Wstring overload of Get_Point.
#include "shared/ini_class.hpp"

INIPoint3D INIClass::Get_Point(Wstring const &section, Wstring const &entry, INIPoint3D const &defvalue) const
{
    return Get_Point(section.Peek_Buffer(), entry.Peek_Buffer(), defvalue);
}
