// Wstring Wstring::As_Lower() const (0x0076EE70): a lowercased copy.
#include "shared/wstring.hpp"

Wstring Wstring::As_Lower() const
{
    Wstring copy(*this);
    copy.To_Lower();
    return copy;
}
