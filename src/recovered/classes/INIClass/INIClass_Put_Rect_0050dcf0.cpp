// INIClass::Put_Rect (0x0050DCF0)
// Wstring overload of Put_Rect.
#include "shared/ini_class.hpp"

bool INIClass::Put_Rect(Wstring const &section, Wstring const &entry, INIRect const &value)
{
    return Put_Rect(section.Peek_Buffer(), entry.Peek_Buffer(), value);
}
