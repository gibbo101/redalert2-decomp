// bool WideString::Insert(unsigned short const *string, unsigned position) (0x007704C0)
// Inserts string at position (clamped to the length); with no text it just takes the
// string (TibSun Wstring::insert shape: the moved tail is counted in characters).
#include "shared/wide_string.hpp"
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
// @ref _memmove=00783290
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" void *__cdecl memmove(void *destination, void const *source, unsigned int count);
extern "C" void *__cdecl memset(void *destination, int value, unsigned int count);

bool WideString::Insert(unsigned short const *string, unsigned position)
{
    if (Buffer == 0) {
        *this = string;
        return true;
    }
    if (position > wcslen(Buffer)) {
        position = wcslen(Buffer);
    }
    unsigned short *buffer = new unsigned short[wcslen(Buffer) + wcslen(string) + 1];
    memset(buffer, 0, (wcslen(Buffer) + wcslen(string) + 1) * 2);
    wcscpy(buffer, Buffer);
    int count = wcslen(Buffer) + 1 - position;
    memmove(buffer + position + wcslen(string), buffer + position, count * 2);
    memmove(buffer + position, string, wcslen(string) * 2);
    delete Buffer;
    Buffer = buffer;
    return true;
}
