// int NullModemClass::Number_Of(char *text) (0x005D1ED0)
// The value of an all-digit string; -1 when any character is not a digit.
#include "shared/null_modem.hpp"
// @ref _isdigit=00782b8c
// @ref _atoi=00782dfd

extern "C" int __cdecl isdigit(int character);
extern "C" int __cdecl atoi(char const *string);
extern "C" unsigned int __cdecl strlen(char const *string);
#pragma intrinsic(strlen)

int NullModemClass::Number_Of(char *text)
{
    int length = strlen(text);
    for (int i = 0; i < length; i++) {
        if (!isdigit(text[i])) {
            return -1;
        }
    }
    return atoi(text);
}
