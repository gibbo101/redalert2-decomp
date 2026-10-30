// INIClass::Get_Vector (0x00510020)
// Wstring overload of Get_Vector.
#include "shared/ini_class.hpp"

INIVector3 INIClass::Get_Vector(Wstring const &section, Wstring const &entry, INIVector3 const &defvalue) const
{
    return Get_Vector(section.Peek_Buffer(), entry.Peek_Buffer(), defvalue);
}
