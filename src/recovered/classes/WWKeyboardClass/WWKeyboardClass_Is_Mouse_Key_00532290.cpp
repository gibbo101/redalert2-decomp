// int __fastcall WWKeyboardClass::Is_Mouse_Key(KeyNumType key) (0x00532290)
// Whether the key (low byte) is a mouse button: VK_LBUTTON, VK_MBUTTON or
// VK_RBUTTON.
#include "shared/keyboard.hpp"

int __fastcall WWKeyboardClass::Is_Mouse_Key(KeyNumType key)
{
    key &= 0xFF;
    return key == 1 || key == 4 || key == 2;
}
