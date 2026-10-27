// INIClass::Is_Section_Header (0x00510790)
// True when the line, after leading whitespace, starts with '[' and contains
// a ']'.
#include "shared/ini_class.hpp"

bool __fastcall INIClass::Is_Section_Header(char const *line)
{
    if (line != 0) {
        while (*line != '\0' && (unsigned char)*line <= ' ') {
            line++;
        }
        if (*line == '[' && strchr(line, ']') != 0) {
            return true;
        }
    }
    return false;
}
