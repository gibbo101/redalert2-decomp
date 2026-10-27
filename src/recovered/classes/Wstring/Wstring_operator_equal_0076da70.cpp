// bool Wstring::operator==(Wstring const &other) const (0x0076DA70)
// Null-aware string equality comparison (strcmp).
#include "shared/wstring.hpp"

bool Wstring::operator==(Wstring const &other) const
{
    if (Buffer == 0 && other.Buffer == 0) {
        return true;
    }
    if (Buffer == 0 || other.Buffer == 0) {
        return false;
    }
    if (strcmp(Buffer, other.Buffer) == 0) {
        return true;
    }
    return false;
}
