// int WWKeyboardClass::Available() (0x00532E60)
// The number of free slots in the queue.
// Assumes: not called out of line (the copy is the unit's own; every use in
// keyboard.cpp is expanded).
#include "shared/keyboard.hpp"

int WWKeyboardClass::Available()
{
    return 256 - abs(Tail - Head);
}
