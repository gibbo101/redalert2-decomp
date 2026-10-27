// WWKeyboardClass::WWKeyboardClass() (0x00532130)
// Empty queue, no mouse position, all keys up.
#include "shared/keyboard.hpp"
#include "shared/crt_memory.hpp"

WWKeyboardClass::WWKeyboardClass() :
    MouseQX(0),
    MouseQY(0),
    unknown_0C(0, 0),
    Head(0),
    Tail(0)
{
    memset(KeyState, 0, sizeof(KeyState));
}
