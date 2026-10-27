// INIClass::Put_Hex (0x0050E1D0)
// Wstring overload of Put_Hex.
#include "shared/ini_class.hpp"

bool INIClass::Put_Hex(Wstring const &section, Wstring const &entry, int number)
{
    return Put_Hex(section.Peek_Buffer(), entry.Peek_Buffer(), number);
}
