// INIClass::Put_Vector (0x0050FDF0)
// Wstring overload of Put_Vector.
#include "shared/ini_class.hpp"

bool INIClass::Put_Vector(Wstring const &section, Wstring const &entry, INIVector3 const &value)
{
    return Put_Vector(section.Peek_Buffer(), entry.Peek_Buffer(), value);
}
