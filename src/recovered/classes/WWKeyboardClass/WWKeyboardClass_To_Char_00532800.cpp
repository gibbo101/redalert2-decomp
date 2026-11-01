// char WWKeyboardClass::To_Char(KeyNumType key) (0x00532800)
// The character of a queued key for a text field: backspace, return and escape pass through,
// 0x0A gives the character queued after it (unknown_08, return as 0), 0x23 a backslash,
// 0x24 a backspace; released keys (0x800) and others give 0.
#include "shared/keyboard.hpp"

char WWKeyboardClass::To_Char(KeyNumType key)
{
    if ((key & 0x800) == 0) {
        KeyNumType ch = (KeyNumType)(key & 0xFF);
        switch (ch) {
            case 0x24:
                return 0x08;


            case 0x23:
                return '\\';

            case 0x0A:
            {
                char character = (char)unknown_08;
                if (character == 0x0D) {
                    character = 0;
                }
                unknown_08 = 0;
                return character;
            }

            case 0x08:
            case 0x0D:
            case 0x1B:
                return (char)ch;
        }
    }
    return 0;
}
