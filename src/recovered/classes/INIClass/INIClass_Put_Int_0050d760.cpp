// INIClass::Put_Int (0x0050D760)
// Wstring overload of Put_Int.
#include "shared/ini_class.hpp"

bool INIClass::Put_Int(Wstring const &section, Wstring const &entry, int number, int format)
{
    return Put_Int(section.Peek_Buffer(), entry.Peek_Buffer(), number, format);
}
