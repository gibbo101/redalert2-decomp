// bool Wstring::Contains_Any(Wstring const &characters) const (0x0076F960)
#include "shared/wstring.hpp"

bool Wstring::Contains_Any(Wstring const &characters) const
{
    return Contains_Any(characters.Peek_Buffer());
}
