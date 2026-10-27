// unsigned short WideString::Get_Char(unsigned index) const (0x00770470):
// the character at index, 0 past the end. (A plain `return 0;` compiles to
// xor ax,ax; the original's xor eax,eax comes from the 16-bit typed zero of
// the conditional.)
#include "shared/wide_string.hpp"
// @ref _wcslen=00783605

extern "C" unsigned int __cdecl wcslen(unsigned short const *string);

unsigned short WideString::Get_Char(unsigned index) const
{
    return index < wcslen(Buffer) ? Buffer[index] : (unsigned short)0;
}
