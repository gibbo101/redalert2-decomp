// bool Wstring::Truncate(unsigned length) (0x0076F060)
// Keeps the first length characters, through a temporary; true.
#include "shared/wstring.hpp"

bool Wstring::Truncate(unsigned length)
{
    Wstring part;
    part.Set(length, Peek_Buffer());
    *this = part.Peek_Buffer();
    return true;
}
