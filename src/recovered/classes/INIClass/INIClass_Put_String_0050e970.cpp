// INIClass::Put_String (0x0050E970)
// Wstring overload of Put_String.
#include "shared/ini_class.hpp"

bool INIClass::Put_String(Wstring const &section, Wstring const &entry, Wstring const &string)
{
    return Put_String(section.Peek_Buffer(), entry.Peek_Buffer(), string.Peek_Buffer());
}
