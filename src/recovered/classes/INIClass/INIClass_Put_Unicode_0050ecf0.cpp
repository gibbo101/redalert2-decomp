// INIClass::Put_Unicode (0x0050ECF0)
// Stores a wide string as comma-terminated hexadecimal character codes
// ("41,42,"); the text is built in a heap buffer of eight bytes per
// character. Name hypothesis (the reader is Get_Unicode 0x0050EDF0).
#include "shared/ini_class.hpp"

extern "C" char *__cdecl _itoa(int value, char *buffer, int radix);
extern "C" char *__cdecl strcat(char *destination, char const *source);
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
#pragma intrinsic(strcat)

bool INIClass::Put_Unicode(char const *section, char const *entry, unsigned short const *string)
{
    bool result = false;

    if (string != 0) {
        int length = wcslen(string) * 8;
        char *buffer = new char[length + 1];
        if (buffer != 0) {
            char *ptr = buffer;
            *ptr = 0;
            for (; *string != 0; string++) {
                _itoa(*string, ptr, 16);
                strcat(ptr, ",");
                ptr = buffer + strlen(buffer);
            }
            result = Put_String(section, entry, buffer);
            delete [] buffer;
        }
    }
    return result;
}
// @ref _wcslen=00783605
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref __itoa=0078db27
