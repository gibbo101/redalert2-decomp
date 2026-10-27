// wchar_t *__fastcall wcstrim(wchar_t *buffer) (0x006EEF80)
#include "shared/object.hpp"

wchar_t *__fastcall wcstrim(wchar_t *buffer)
{
    if (buffer != 0) {
        wchar_t *source = buffer;
        while (*source != 0 && *source <= L' ') {
            source++;
        }
        if (source != buffer) {
            wcscpy(buffer, source);
        }
        for (int index = wcslen(buffer) - 1; index >= 0; index--) {
            if (*source != 0 && buffer[index] <= L' ') {
                buffer[index] = 0;
            } else {
                break;
            }
        }
    }
    return buffer;
}
