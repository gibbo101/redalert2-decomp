// VeinholeMonsterClass *VeinholeMonsterClass::Find_Covering(Cell const &cell) (0x007101B0)
// The last monster in Array whose per-cell table (+0xB0) has a byte set at the cell, or null.
#include "shared/veinhole.hpp"
// @ref ?unknown_cell_index_428a90@@YIHABVCell@@@Z=00428a90

VeinholeMonsterClass *__fastcall VeinholeMonsterClass::Find_Covering(::Cell const &cell)
{
    for (int index = Array.Count() - 1; index >= 0; index--) {
        if (Array[index]->unknown_b0[unknown_cell_index_428a90(cell)] != 0) {
            return Array[index];
        }
    }
    return 0;
}
