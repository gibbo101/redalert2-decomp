// INIClass::Strip_Comments (0x00510760)
// Cuts a line at its first ';' and trims what remains.
#include "shared/ini_class.hpp"

void __fastcall INIClass::Strip_Comments(char *buffer)
{
    if (buffer != 0) {
        char *comment = strchr(buffer, ';');
        if (comment != 0) {
            *comment = '\0';
            strtrim(buffer);
        }
    }
}
