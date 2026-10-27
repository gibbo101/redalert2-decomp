// int __fastcall Unknown_0056A900(int row1, int row2) (0x0056A900)
// The row of the 12 x 8 table at 0x007E00C4 that best matches two of its
// rows: a row qualifies when it has no 1 where either row has a 2; the
// qualifying row with the most 1s shared by both rows wins (the first on a
// tie); -1 when none has any.
#include "shared/map.hpp"
// @ref ?unknown_table_7e00c4@@3PAY07HA=007e00c4

int __fastcall Unknown_0056A900(int row1, int row2)
{
    int best = -1;
    int best_count = 0;
    for (int row = 0; row < 12; row++) {
        bool ok = true;
        int count = 0;
        for (int index = 0; index < 8; index++) {
            int value1 = unknown_table_7e00c4[row1][index];
            int value2 = unknown_table_7e00c4[row2][index];
            int value = unknown_table_7e00c4[row][index];
            if ((value1 == 2 || value2 == 2) && value == 1) {
                ok = false;
            }
            if (value1 == value && value2 == value && value == 1) {
                count++;
            }
        }
        if (ok && count > best_count) {
            best_count = count;
            best = row;
        }
    }
    return best;
}
