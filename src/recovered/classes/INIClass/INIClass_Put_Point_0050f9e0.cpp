// INIClass::Put_Point (0x0050F9E0)
// Wstring overload of Put_Point.
#include "shared/ini_class.hpp"

bool INIClass::Put_Point(Wstring const &section, Wstring const &entry, INIPoint3D const &value)
{
    return Put_Point(section.Peek_Buffer(), entry.Peek_Buffer(), value);
}
