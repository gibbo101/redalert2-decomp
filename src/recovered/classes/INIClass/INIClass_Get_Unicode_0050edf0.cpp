// INIClass::Get_Unicode (0x0050EDF0)
// Reads a wide string written by Put_Unicode (comma-separated hexadecimal
// character codes) into buffer, at most size characters, null terminated;
// copies defvalue when the entry is missing or empty. Returns the length.
// Name hypothesis.
#include "shared/ini_class.hpp"
#include "shared/crt_tokens.hpp"
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_C@_02BDCN@?$CFx?$AA@=007db4b4

extern "C" unsigned short *__cdecl wcsncpy(unsigned short *dest, unsigned short const *source, unsigned int count);
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);

int INIClass::Get_Unicode(char const *section, char const *entry, unsigned short const *defvalue, unsigned short *buffer, int size) const
{
    char text[0x5000];

    int length = Get_String(section, entry, 0, text, sizeof(text));
    if (length == 0) {
        wcsncpy(buffer, defvalue, size);
        return wcslen(buffer);
    }

    char *token = strtok(text, ",");
    unsigned short *ptr = buffer;
    while (token != 0 && size != 0) {
        int value;
        sscanf(token, "%x", &value);
        *ptr++ = (unsigned short)value;
        token = strtok(0, ",");
        size--;
    }
    *ptr = 0;
    return wcslen(buffer);
}
