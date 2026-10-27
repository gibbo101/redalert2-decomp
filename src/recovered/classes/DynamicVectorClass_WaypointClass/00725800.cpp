// 0x00725800: function not yet identified
//
// Owner: DynamicVectorClass<WaypointClass>, virtual slot 4 (vtable +0x10) (from RTTI/vtables).
// Body: 64 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: int __thiscall FUN_00725800(int param_1,int *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00725800 {

struct Owner_00725800 { int FUN_00725800(int *param_2); };

int Owner_00725800::FUN_00725800(int *param_2)
{
    int param_1 = (int)this;
    int iVar1;
    int *piVar2;

    iVar1 = (int)(0);
    if (0 < *(int *)(param_1 + 0x10)) {
        piVar2 = (int *)(*(int **)(param_1 + 4));
        do {
            if (((*piVar2 == *param_2) && (piVar2[1] == param_2[1])) && (piVar2[2] == param_2[2])) {
                return iVar1;
            }
            iVar1 = (int)(iVar1 + 1);
            piVar2 = (int *)(piVar2 + 3);
        } while (iVar1 < *(int *)(param_1 + 0x10));
    }
    return -1;
}

}  // namespace seed_00725800
