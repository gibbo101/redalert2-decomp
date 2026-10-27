// int Wstring::Get_Token(int start, char const *separators, Wstring &token) const (0x0076F200)
// Skips separators from start, copies the run up to the next separator into
// token and returns the position after it; -1 for a negative start or when
// only separators remain.
#include "shared/wstring.hpp"

int Wstring::Get_Token(int start, char const *separators, Wstring &token) const
{
    if (start < 0) {
        return -1;
    }
    while (start < (int)Length() && strchr(separators, Buffer[start])) {
        start++;
    }
    if (start >= (int)Length()) {
        return -1;
    }
    int first = start;
    while (start < (int)Length() && !strchr(separators, Buffer[start])) {
        start++;
    }
    int last = start - 1;
    token = Buffer + first;
    token.Truncate(last - first + 1);
    return last + 1;
}
