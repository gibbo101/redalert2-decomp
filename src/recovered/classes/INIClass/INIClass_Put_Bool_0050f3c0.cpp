// INIClass::Put_Bool (0x0050F3C0)
// Wstring overload of Put_Bool.
#include "shared/ini_class.hpp"

bool INIClass::Put_Bool(Wstring const &section, Wstring const &entry, bool value)
{
    return Put_Bool(section.Peek_Buffer(), entry.Peek_Buffer(), value);
}
