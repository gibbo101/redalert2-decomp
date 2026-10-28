// int MessageListClass::Trim_Message(dest, src, min_chars, max_chars, scan_start) -- 0x005B5CB0
// Moves the first characters of src (at least min_chars, at most max_chars, broken after a space found
// scanning forward from min_chars, or backward from max_chars when scan_start is set) into dest when it
// is given; src keeps the rest. The number of characters taken (0 when min_chars is not positive).
// @ref _wcslen=00783605
// @ref _memmove=00783290
#include "shared/message_list.hpp"
#include "shared/crt_memory.hpp"
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);

int MessageListClass::Trim_Message(unsigned short *dest, unsigned short *src, int min_chars, int max_chars, int scan_start)
{
    if (min_chars <= 0) {
        return 0;
    }
    int len = wcslen(src);
    if (max_chars > len) {
        max_chars = len;
    }
    int i;
    bool found = false;
    if (scan_start == 0) {
        for (i = min_chars; i <= max_chars; i++) {
            if (src[i - 1] != 0 && src[i - 1] <= ' ') {
                found = true;
                break;
            }
        }
    } else {
        for (i = max_chars; i >= min_chars; i--) {
            if (src[i - 1] != 0 && src[i - 1] <= ' ') {
                found = true;
                break;
            }
        }
    }
    if (!found) {
        i = min_chars;
    }
    if (dest) {
        memcpy(dest, src, i * 2);
        dest[i] = 0;
    }
    memmove(src, &src[i], (len - i + 1) * 2);
    return i;
}
