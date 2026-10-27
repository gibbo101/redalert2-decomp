// bool Wstring::Concatenate(Wstring const &other) (0x0076DE40)
// Appends another Wstring.
#include "shared/wstring.hpp"

bool Wstring::Concatenate(Wstring const &other)
{
    return Concatenate(other.Peek_Buffer());
}
