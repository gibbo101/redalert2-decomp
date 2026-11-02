// void TagClass::unknown_func_6b3fe0(int value) (0x006B3FE0)
// Passes value to the attached chain's 0x006ED650 reset (the companion of 0x006B3FD0).
#include "shared/object.hpp"

void TagClass::unknown_func_6b3fe0(int value)
{
    AttachedTrigger->unknown_func_6ed650(value);
}
