// char Wstring::operator()(unsigned index) const (0x0076E770)
// Character at `index`, or 0 past the end.
#include "shared/wstring.hpp"

char Wstring::operator()(unsigned index) const
{
    if (index < strlen(Buffer)) {
        return Buffer[index];
    }
    return '\0';
}
