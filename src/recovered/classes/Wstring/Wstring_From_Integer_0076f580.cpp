// Wstring __fastcall Wstring_From_Integer(int value) (0x0076F580)
// The decimal text of value.
#include "shared/wstring.hpp"

Wstring __fastcall Wstring_From_Integer(int value)
{
    char buffer[16];
    sprintf(buffer, "%d", value);
    return Wstring(buffer);
}
