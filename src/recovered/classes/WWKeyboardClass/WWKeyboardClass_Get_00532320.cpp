// KeyNumType WWKeyboardClass::Get() (0x00532320)
// Waits for a key and removes it (see Buff_Get).
#include "shared/keyboard.hpp"
// @ref ?Unknown_005B5EE0@@YAXXZ=005b5ee0
// @ref ?Is_Buffer_Full@WWKeyboardClass@@AAE_NXZ=00532980
// @ref ?Peek_Element@WWKeyboardClass@@AAEGXZ=00532920

KeyNumType WWKeyboardClass::Get()
{
    while (!Check()) {
    }
    return Buff_Get();
}
