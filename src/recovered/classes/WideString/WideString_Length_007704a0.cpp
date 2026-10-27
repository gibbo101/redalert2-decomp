// unsigned WideString::Length() const (0x007704A0): wcslen; 0 for no text.
#include "shared/wide_string.hpp"
// @ref _wcslen=00783605

extern "C" unsigned int __cdecl wcslen(unsigned short const *string);

unsigned WideString::Length() const
{
    if (Buffer == 0) {
        return 0;
    }
    return wcslen(Buffer);
}
