// 0x005b6830: function not yet identified
//
// Owner: DynamicVectorClass<AcceleratorTracker>, virtual slot 4 (vtable +0x10) (from RTTI/vtables).
// Body: 54 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: int __thiscall FUN_005b6830(int param_1,int *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005b6830 {

struct Owner_005b6830 { int FUN_005b6830(int *param_2); };

int Owner_005b6830::FUN_005b6830(int *param_2)
{
    int param_1 = (int)this;
    int iVar1;
    int *piVar2;

    iVar1 = (int)(0);
    if (0 < *(int *)(param_1 + 0x10)) {
        piVar2 = (int *)(*(int **)(param_1 + 4));
        do {
            if ((*piVar2 == *param_2) && (piVar2[1] == param_2[1])) {
                return iVar1;
            }
            iVar1 = (int)(iVar1 + 1);
            piVar2 = (int *)(piVar2 + 2);
        } while (iVar1 < *(int *)(param_1 + 0x10));
    }
    return -1;
}

}  // namespace seed_005b6830
