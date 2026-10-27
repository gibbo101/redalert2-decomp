// bool WWKeyboardClass::Is_Buffer_Empty() (0x005329A0)
// Written as an if with two returns (see Is_Buffer_Full).
#include "shared/keyboard.hpp"

bool WWKeyboardClass::Is_Buffer_Empty()
{
    if (Head == Tail) {
        return true;
    }
    return false;
}
