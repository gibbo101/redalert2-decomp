// INIClass::Get_Entry (0x0050CED0)
// Wstring overload of Get_Entry; returns the key as a new Wstring (empty
// when there is no such entry).
#include "shared/ini_class.hpp"

Wstring INIClass::Get_Entry(Wstring const &section, int index) const
{
    return Get_Entry(section.Peek_Buffer(), index);
}
