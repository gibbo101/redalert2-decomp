// bool WWKeyboardClass::Is_Buffer_Full() (0x00532980)
// Written as an if with two returns: the expression forms compile alike
// standalone but are cheaper to inline, and the original's callers
// (Buff_Get, Get) stop expanding at it.
#include "shared/keyboard.hpp"

bool WWKeyboardClass::Is_Buffer_Full()
{
    if ((Tail + 1) % 256 == Head) {
        return true;
    }
    return false;
}
