// INIClass::Get_String (0x0050EB40)
// Wstring overload of Get_String: reads into a 1023-character buffer, which
// is then assigned to result (empty when there is no value and no default).
// Returns the length.
#include "shared/ini_class.hpp"

int INIClass::Get_String(Wstring const &section, Wstring const &entry, Wstring const &defvalue, Wstring &result) const
{
    char buffer[1024];
    int length = Get_String(section.Peek_Buffer(), entry.Peek_Buffer(), defvalue.Peek_Buffer(), buffer,
                            sizeof(buffer) - 1);
    result = buffer;
    return length;
}
