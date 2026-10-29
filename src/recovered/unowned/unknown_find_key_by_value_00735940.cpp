// void *__fastcall Unknown_00735940(int value) -- 0x00735940
// Purpose: in the dialog stack (shared/win32_window.hpp) at 0x00B25BB8 (count at
// 0x00B25DE0; also 0x00735970/0x007359B0), the key of the last entry whose
// value equals value; null when there is none. 0x0074D780 looks up entry
// 0xC4 with it and uses the key as a window.
// Assumptions: the table's meaning (window per id) and the names are
// hypotheses.

// @ref ?DialogStack@@3PAUDialogStackEntry@@A=00b25bb8
// @ref ?DialogStackCount@@3HA=00b25de0
#include "shared/win32_window.hpp"

void *__fastcall Unknown_00735940(int value)
{
    for (int index = DialogStackCount - 1; index >= 0; index--) {
        if (value == DialogStack[index].Resource) {
            return DialogStack[index].Window;
        }
    }
    return 0;
}
