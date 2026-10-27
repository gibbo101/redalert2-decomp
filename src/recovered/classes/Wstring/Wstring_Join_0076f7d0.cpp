// Wstring __fastcall Wstring_Join(Wstring const &left, Wstring const &right) (0x0076F7D0)
// left followed by right (the member operator+ with Concatenate expanded;
// callers 0x007286B3, 0x0072ADA0, ...). The name is a hypothesis: a free
// operator+ would be ambiguous with the member one.
#include "shared/wstring.hpp"

Wstring __fastcall Wstring_Join(Wstring const &left, Wstring const &right)
{
    Wstring result(left);
    result.Concatenate(right);
    return result;
}
