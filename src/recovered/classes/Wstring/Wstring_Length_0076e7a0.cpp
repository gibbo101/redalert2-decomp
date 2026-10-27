// unsigned Wstring::Length() const (0x0076E7A0)
// Length in characters (0 when null).
#include "shared/wstring.hpp"

unsigned Wstring::Length() const
{
    if (!Buffer) {
        return 0;
    }
    return strlen(Buffer);
}
