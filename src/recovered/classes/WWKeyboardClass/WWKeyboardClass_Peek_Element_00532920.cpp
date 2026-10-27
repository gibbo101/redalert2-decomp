// KeyNumType WWKeyboardClass::Peek_Element() (0x00532920)
// The next queued element without removing it, 0 when empty.
#include "shared/keyboard.hpp"

KeyNumType WWKeyboardClass::Peek_Element()
{
    if (!Is_Buffer_Empty()) {
        return Buffer[Head];
    }
    return 0;
}
