// XMP_Decode_ASCII(char const *str, digit *number, int precision) (0x005A8F00)
// Parses an optionally negative number; a trailing H, O or B selects
// hexadecimal, octal or binary (default decimal); commas are ignored.
// Body includes the switch jump tables (0x005A90D0-0x005A9105).
// @ref _toupper=007829d3
// @ref _isxdigit=00782bb4
// @ref _isdigit=00782b8c
#include "shared/mpmath.hpp"

extern "C" int __cdecl toupper(int c);
extern "C" int __cdecl isxdigit(int c);
extern "C" int __cdecl isdigit(int c);
extern "C" unsigned int __cdecl strlen(char const *str);
#pragma intrinsic(strlen)

void __fastcall XMP_Decode_ASCII(char const *str, digit *mpn, int precision)
{
    XMP_Init(mpn, 0, precision);

    if (!str) return;
    int i = strlen(str);
    if (i == 0) return;

    unsigned short radix;
    switch (toupper(str[i-1])) {
        case '.':
            radix = 10;
            break;

        case 'H':
            radix = 16;
            break;

        case 'O':
            radix = 8;
            break;

        case 'B':
            radix = 2;
            break;

        default:
            radix = 10;
            break;
    }

    bool minus = (*str == '-');
    if (minus) str++;

    digit c;
    while ((c = (unsigned char)*str++) != 0) {
        if (c == ',') continue;

        if (!isxdigit((char)c)) break;

        if (isdigit((char)c)) {
            c -= '0';
        } else {
            c = (unsigned char)(toupper((char)c) - 'A') + 10;
        }

        if (c >= radix) break;


        XMP_Unsigned_Mult_Int(mpn, mpn, radix, precision);
        XMP_Add_Int(mpn, mpn, c, 0, precision);
    }
    if (minus) {
        XMP_Neg(mpn, precision);
    }
}

