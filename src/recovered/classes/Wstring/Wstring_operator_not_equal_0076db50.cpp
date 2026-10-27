// bool Wstring::operator!=(Wstring const &other) const (0x0076DB50)
// Null-aware string inequality comparison (strcmp).
#include "shared/wstring.hpp"

bool Wstring::operator!=(Wstring const &other) const
{
    if (Buffer == 0 && other.Buffer == 0) {
        return false;
    }
    if (Buffer == 0 || other.Buffer == 0) {
        return true;
    }
    if (strcmp(Buffer, other.Buffer) != 0) {
        return true;
    }
    return false;
}
