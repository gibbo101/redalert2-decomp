// VeinholeMonsterClass *VeinholeMonsterClass::Find_At(Cell const &cell) (0x00710160)
// The last monster in Array whose cell is cell, or null.
#include "shared/veinhole.hpp"
#include "shared/house.hpp"

VeinholeMonsterClass *__fastcall VeinholeMonsterClass::Find_At(::Cell const &cell)
{
    for (int index = Array.Count() - 1; index >= 0; index--) {
        if (Array[index]->Cell == cell) {
            return Array[index];
        }
    }
    return 0;
}
