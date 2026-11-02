// void TActionClass::Set_Text(char const *text) (0x006B2EC0)
// Keeps text without its leading and trailing white space (31 characters).
#include "shared/object.hpp"

void TActionClass::Set_Text(char const *text)
{
    Text[0] = 0;
    if (text != 0) {
        while (*text != 0 && (unsigned char)*text <= ' ') {
            text++;
        }
        if (*text != 0) {
            strncpy(Text, text, sizeof(Text) - 1);
            Text[sizeof(Text) - 1] = 0;
            int length = strlen(Text);
            while (length != 0 && (unsigned char)Text[length - 1] <= ' ') {
                length--;
            }
            Text[length] = 0;
        }
    }
}


