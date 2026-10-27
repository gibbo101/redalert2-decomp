// KeyNumType WWKeyboardClass::Fetch_Element() (0x005328E0)
// Removes and returns the next queued element, 0 when empty.
#include "shared/keyboard.hpp"

KeyNumType WWKeyboardClass::Fetch_Element()
{
    KeyNumType value = 0;
    if (Head != Tail) {
        value = Buffer[Head];
        Head = (Head + 1) % 256;
    }
    return value;
}
