// INIClass::Put_TextBlock (0x0050D310)
// Replaces the section with the text split into entries "1", "2", ...: each
// holds at most 75 characters, a longer piece broken back at a whitespace
// byte, trimmed. Always true once the section is named.
#include "shared/ini_class.hpp"
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc

bool INIClass::Put_TextBlock(char const *section, char const *text)
{
    if (section == 0) return false;

    Clear(section);

    int index = 1;
    while (text != 0 && *text != '\0') {

        char buffer[128];

        strncpy(buffer, text, 75);
        buffer[75] = '\0';

        char b[32];
        sprintf(b, "%d", index);

        int count = strlen(buffer);
        if (count > 0) {
            if (count >= 75) {
                while (count) {
                    char c = buffer[count];

                    if (c != '\0' && (unsigned char)c <= ' ') break;
                    count--;
                }

                if (count == 0) {
                    break;
                } else {
                    buffer[count] = '\0';
                }
            }

            strtrim(buffer);
            Put_String(section, b, buffer);
            index++;
            text = text + count;
        } else {
            break;
        }
    }
    return true;
}
