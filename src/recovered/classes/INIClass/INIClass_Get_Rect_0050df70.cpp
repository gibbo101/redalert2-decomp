// INIClass::Get_Rect (0x0050DF70)
// Wstring overload of Get_Rect.
#include "shared/ini_class.hpp"

INIRect INIClass::Get_Rect(Wstring const &section, Wstring const &entry, INIRect const &defvalue) const
{
    return Get_Rect(section.Peek_Buffer(), entry.Peek_Buffer(), defvalue);
}
