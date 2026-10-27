// void HouseClass::unknown_func_4f3b70(SuperClass *super) (0x004F3B70)
// While the house has an enemy (+0x54F0), fires the super weapon at the
// empty cell 0x00A40F10.
// @ref ?unknown_cell_a40f10@@3VCell@@A=00a40f10
#include "shared/techno.hpp"

void HouseClass::unknown_func_4f3b70(SuperClass *super)
{
    if (unknown_54f0 != -1) {
        unknown_func_4e68d0(Supers.ID(super), &unknown_cell_a40f10);
    }
}
