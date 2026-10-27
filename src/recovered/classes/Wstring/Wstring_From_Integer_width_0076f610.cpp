// Wstring __fastcall Wstring_From_Integer(int value, int width) (0x0076F610)
// The decimal text of value, zero-padded to width (the format is built in
// the output buffer and used in place, as in the original).
#include "shared/wstring.hpp"

Wstring __fastcall Wstring_From_Integer(int value, int width)
{
    char buffer[16];
    sprintf(buffer, "%%0%dd", width);
    sprintf(buffer, buffer, value);
    return Wstring(buffer);
}
