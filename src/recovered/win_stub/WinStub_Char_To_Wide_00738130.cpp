// wchar_t Char_To_Wide_00738130(unsigned character) (0x00738130)
// The wide character of a single or double byte character code (lead byte in bits 8-15);
// 0 when MultiByteToWideChar does not produce exactly one character.
#include "shared/win_stub.hpp"
#include "shared/win32_api.hpp"
#include "shared/crt_string.hpp"

unsigned short __fastcall Char_To_Wide_00738130(unsigned int character);
// @ref __imp__MultiByteToWideChar@24=0079a1b8

unsigned short __fastcall Char_To_Wide_00738130(unsigned int character)
{
    char text[3];
    if (character & 0xFF00) {
        text[0] = (char)(character >> 8);
        text[1] = (char)character;
        text[2] = 0;
    } else {
        text[0] = (char)character;
        text[1] = 0;
    }
    unsigned int wide;
    return (MultiByteToWideChar(0, 0, text, strlen(text), (unsigned short *)&wide, 1) == 1) ? wide : 0;
}
