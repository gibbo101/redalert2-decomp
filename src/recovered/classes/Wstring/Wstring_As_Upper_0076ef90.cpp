// Wstring Wstring::As_Upper() const (0x0076EF90): a uppercased copy.
#include "shared/wstring.hpp"

Wstring Wstring::As_Upper() const
{
    Wstring copy(*this);
    copy.To_Upper();
    return copy;
}
