// INIClass::Put_Unicode (0x0050EDC0)
// Wstring overload of Put_Unicode (name hypothesis, like the char form).
#include "shared/ini_class.hpp"
#include "shared/wide_string.hpp"

bool INIClass::Put_Unicode(Wstring const &section, Wstring const &entry, WideString const &string)
{
    return Put_Unicode(section.Peek_Buffer(), entry.Peek_Buffer(), string.unknown_text_770430());
}
