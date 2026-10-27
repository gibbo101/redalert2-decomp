// char *__fastcall strtrim(char *buffer) (0x006EEF10)
#include "shared/object.hpp"

char *__fastcall strtrim(char *buffer)
{
    if (buffer != 0) {
        char *source = buffer;
        while (*source != 0 && (unsigned char)*source <= ' ') {
            source++;
        }
        if (source != buffer) {
            strcpy(buffer, source);
        }
        for (int index = strlen(buffer) - 1; index >= 0; index--) {
            if (*source != 0 && (unsigned char)buffer[index] <= ' ') {
                buffer[index] = 0;
            } else {
                break;
            }
        }
    }
    return buffer;
}
