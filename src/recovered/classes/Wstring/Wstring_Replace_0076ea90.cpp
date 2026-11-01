// bool Wstring::Replace(char const *find, char const *with) (0x0076EA90)
// Replaces every occurrence of find with `with` (the narrow form of
// WideString::Replace 0x007706E0).
#include "shared/wstring.hpp"
// @ref _strstr=007836b0
// @ref _strncat=00784750
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??_C@_00A@?$AA@=0083c55c

bool Wstring::Replace(char const *find, char const *with)
{
    Wstring result;
    char const *current = Get();
    while (current != 0 && *current != 0) {
        char const *found = strstr(current, find);
        if (found == 0) {
            result.Concatenate(current);
            break;
        }
        int length = found - current;
        if (length != 0) {
            char *old = result.Buffer;
            unsigned size = length + 1;
            if (old != 0) {
                size += strlen(old);
            }
            result.Buffer = new char[size];
            if (old != 0) {
                strcpy(result.Buffer, old);
            } else {
                result.Buffer[0] = 0;
            }
            strncat(result.Buffer, current, length);
            if (old != 0) {
                delete old;
            }
        }
        if (with != 0) {
            result.Concatenate(with);
        }
        current = found + strlen(find);
        if (current == 0) {
            break;
        }
    }
    *this = result.Peek_Buffer();
    return true;
}
