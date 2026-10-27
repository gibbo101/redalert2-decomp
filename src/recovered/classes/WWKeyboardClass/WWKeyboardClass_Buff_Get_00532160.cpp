// KeyNumType WWKeyboardClass::Buff_Get() (0x00532160)
// Waits for a key and removes it with the data queued behind it: the
// position of a mouse key, the character of a 0x0A key.
#include "shared/keyboard.hpp"
// @ref ?Unknown_005B5EE0@@YAXXZ=005b5ee0
// @ref ?Is_Buffer_Full@WWKeyboardClass@@AAE_NXZ=00532980
// @ref ?Is_Buffer_Empty@WWKeyboardClass@@AAE_NXZ=005329a0

KeyNumType WWKeyboardClass::Buff_Get()
{
    while (!Check()) {
    }
    KeyNumType key = Fetch_Element();
    if (Is_Mouse_Key(key)) {
        MouseQX = Fetch_Element();
        MouseQY = Fetch_Element();
        unknown_0C = Point2D(MouseQX, MouseQY);
    } else if (Is_Char_Key(key)) {
        unknown_08 = Fetch_Element();
    }
    return key;
}
