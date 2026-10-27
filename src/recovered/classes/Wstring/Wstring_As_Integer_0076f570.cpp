// int Wstring::As_Integer() const (0x0076F570): atoi of the text.
#include "shared/wstring.hpp"

int Wstring::As_Integer() const
{
    return atoi(Buffer);
}
