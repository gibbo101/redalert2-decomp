// int __fastcall WWKeyboardClass::Is_Char_Key(KeyNumType key) (0x005322C0)
// Whether the key is the 0x0A marker that a character follows in the queue.
// Assumes: name hypothesis.
#include "shared/keyboard.hpp"

int __fastcall WWKeyboardClass::Is_Char_Key(KeyNumType key)
{
    key &= 0xFF;
    return key == 0x0A;
}
