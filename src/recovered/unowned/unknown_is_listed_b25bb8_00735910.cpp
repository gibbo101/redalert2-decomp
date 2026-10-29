// int __fastcall unknown_is_listed_b25bb8(int key) -- 0x00735910
// Purpose: whether key is the first word of one of the 0x00B25DE0 used
// 8-byte records at 0x00B25BB8: whether a window is on the dialog stack.
// Assumptions: the int parameter type is kept from the first recovery.
// @ref ?DialogStack@@3PAUDialogStackEntry@@A=00b25bb8
// @ref ?DialogStackCount@@3HA=00b25de0
#include "shared/win32_window.hpp"

int __fastcall unknown_is_listed_b25bb8(int key)
{
    for (int index = 0; index < DialogStackCount; index++) {
        if ((int)DialogStack[index].Window == key) {
            return 1;
        }
    }
    return 0;
}
