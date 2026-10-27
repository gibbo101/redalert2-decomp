// void HouseClass::unknown_func_4e5dc0(int cell, int amount) (0x004E5DC0)
// Adds an amount (or removes a negative one, clamped at zero) to the
// per-cell values around a cell, halved or quartered by distance.
#include "shared/techno.hpp"

extern int const unknown_adjacent_offset_7d9fa0[9];   // 0x007D9FA0 cell offsets of the 3x3 block (map width 130? hypothesis)
extern int const unknown_adjacent_shift_7d9fc4[9];    // 0x007D9FC4 shifts per block position

void HouseClass::unknown_func_4e5dc0(int cell, int amount)
{
    int negative;
    if (amount < 0) {
        amount = -amount;
        negative = 1;
    } else {
        negative = 0;
    }
    int index = 0;
    for (int count = 9; count != 0; count--, index++) {
        int value = amount >> unknown_adjacent_shift_7d9fc4[index];
        int *entry = &unknown_56d0[unknown_adjacent_offset_7d9fa0[index] + cell];
        if (negative) {
            *entry -= value;
        } else {
            *entry += value;
        }
        if (*entry < 0) {
            *entry = 0;
        }
    }
}
