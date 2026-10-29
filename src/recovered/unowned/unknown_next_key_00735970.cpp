// int __fastcall unknown_next_key(int key) -- 0x00735970
// Purpose: in the dialog stack (shared/win32_window.hpp) at 0x00B25BB8 (count at
// 0x00B25DE0), the key that follows the first entry equal to key; 0 when
// key is absent or last.
// Assumptions: the table's meaning is unidentified; names are placeholders.

// @ref ?DialogStack@@3PAUDialogStackEntry@@A=00b25bb8
// @ref ?DialogStackCount@@3HA=00b25de0
#include "shared/win32_window.hpp"

int __fastcall unknown_next_key(int key)
{
    for (int index = 0; index < DialogStackCount; index++) {
        if (key == (int)DialogStack[index].Window && index < DialogStackCount - 1) {
            return (int)DialogStack[index + 1].Window;
        }
    }
    return 0;
}
