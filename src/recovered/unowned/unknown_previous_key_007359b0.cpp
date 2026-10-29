// int __fastcall unknown_previous_key(int key) -- 0x007359B0
// Purpose: in the dialog stack (shared/win32_window.hpp) at 0x00B25BB8 (count at
// 0x00B25DE0), the key that precedes the last entry equal to key; 0 when
// key is absent or first. The counterpart of 0x00735970.
// Assumptions: the table's meaning is unidentified; names are placeholders.

// @ref ?DialogStack@@3PAUDialogStackEntry@@A=00b25bb8
// @ref ?DialogStackCount@@3HA=00b25de0
#include "shared/win32_window.hpp"

int __fastcall unknown_previous_key(int key)
{
    for (int index = DialogStackCount - 1; index >= 0; index--) {
        if (key == (int)DialogStack[index].Window && index > 0) {
            return (int)DialogStack[index - 1].Window;
        }
    }
    return 0;
}
