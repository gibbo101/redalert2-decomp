// INIClass::Get_Int (0x0050D9D0)
// Wstring overload of Get_Int.
#include "shared/ini_class.hpp"

int INIClass::Get_Int(Wstring const &section, Wstring const &entry, int defvalue) const
{
    return Get_Int(section.Peek_Buffer(), entry.Peek_Buffer(), defvalue);
}
