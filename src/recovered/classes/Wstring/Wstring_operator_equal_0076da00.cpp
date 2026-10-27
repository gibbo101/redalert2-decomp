// bool Wstring::operator==(char const *string) const (0x0076DA00)
// Null-aware string equality comparison (strcmp).
#include "shared/wstring.hpp"

bool Wstring::operator==(char const *string) const
{
    if (Buffer == 0 && string == 0) {
        return true;
    }
    if (Buffer == 0 || string == 0) {
        return false;
    }
    if (strcmp(Buffer, string) == 0) {
        return true;
    }
    return false;
}
