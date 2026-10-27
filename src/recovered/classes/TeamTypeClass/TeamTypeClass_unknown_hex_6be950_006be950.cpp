// static int Hex_To_Int(char const *string) (0x006BE950)
// Parses leading hexadecimal digits (either case); stops at the first other
// character. File-local in the original (no callers found; name hypothesis).
#include "shared/team_type.hpp"
// @ref _isxdigit=00782bb4
// @ref _isdigit=00782b8c
// @ref _toupper=007829d3

int __fastcall TeamTypeClass_unknown_hex_6be950(char const *string)
{
    int value = 0;
    while (isxdigit(*string)) {
        value *= 16;
        if (isdigit(*string)) {
            value += *string - '0';
        } else {
            value += toupper(*string) - 'A' + 10;
        }
        string++;
    }
    return value;
}
