// void VeinholeMonsterClass::All_Draw() (0x00710820)
// Calls unknown_func_710880 on every monster, last first.
#include "shared/veinhole.hpp"
// @ref ?unknown_func_710880@VeinholeMonsterClass@@QAEXXZ=00710880

void __cdecl VeinholeMonsterClass::All_Draw()
{
    for (int index = Array.Count() - 1; index >= 0; index--) {
        Array[index]->unknown_func_710880();
    }
}
