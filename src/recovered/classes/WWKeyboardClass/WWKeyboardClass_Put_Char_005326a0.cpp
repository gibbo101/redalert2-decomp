// bool WWKeyboardClass::Put_Char(KeyNumType character) (0x005326A0)
// Queues the 0x0A marker key followed by a character when two slots are free.
// Assumes: name hypothesis; it has no callers (Message_Handler's WM_CHAR case
// queues the same two keys itself).
#include "shared/keyboard.hpp"
// @ref ?unknown_flag_a40d44@@3_NA=00a40d44

bool WWKeyboardClass::Put_Char(KeyNumType character)
{
    if (unknown_flag_a40d44) {
        return true;
    }
    if (Available() >= 2) {
        Put_Key_Message(0x0A);
        Put(character & 0xFF);
        return true;
    }
    return false;
}
