// bool Wstring::operator!=(char const *string) const (0x0076DAE0)
// Null-aware string inequality comparison (strcmp).
#include "shared/wstring.hpp"

bool Wstring::operator!=(char const *string) const
{
    if (Buffer == 0 && string == 0) {
        return false;
    }
    if (Buffer == 0 || string == 0) {
        return true;
    }
    if (strcmp(Buffer, string) != 0) {
        return true;
    }
    return false;
}
