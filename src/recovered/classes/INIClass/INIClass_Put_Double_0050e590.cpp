// INIClass::Put_Double (0x0050E590)
// Wstring overload of Put_Double.
#include "shared/ini_class.hpp"

bool INIClass::Put_Double(Wstring const &section, Wstring const &entry, double number)
{
    return Put_Double(section.Peek_Buffer(), entry.Peek_Buffer(), number);
}
