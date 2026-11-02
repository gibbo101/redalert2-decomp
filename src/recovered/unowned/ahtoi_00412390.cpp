// int __fastcall ahtoi(char const *str) (0x00412390; TibSun ahtoi.cpp)
// The value of the hexadecimal digits at the start of str (0 for none or no string).
// @ref _isxdigit=00782bb4
// @ref _toupper=007829d3
#include "shared/ahtoi.hpp"
extern "C" int __cdecl isxdigit(int c);
extern "C" int __cdecl toupper(int c);

int __fastcall ahtoi(char const *str)
{
    int value = 0;
    while (str != 0 && isxdigit(*str)) {
        char c = *str;
        value <<= 4;
        str++;
        if (c >= '0' && c <= '9') {
            value += c - '0';
        } else {
            value += toupper(c) - 'A' + 10;
        }
    }
    return value;
}
