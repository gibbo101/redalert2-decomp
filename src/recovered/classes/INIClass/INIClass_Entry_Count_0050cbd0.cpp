// INIClass::Entry_Count (0x0050CBD0)
// Wstring overload of Entry_Count.
#include "shared/ini_class.hpp"

int INIClass::Entry_Count(Wstring const &section) const
{
    return Entry_Count(section.Peek_Buffer());
}
