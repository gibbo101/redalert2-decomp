// 0x006acd00: function not yet identified
//
// Owner: DynamicVectorClass<DirtyAreaStruct>, virtual slot 4 (vtable +0x10) (from RTTI/vtables).
// Body: 95 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: int __thiscall FUN_006acd00(int param_1,int *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006acd00 {

struct Owner_006acd00 { int FUN_006acd00(int *param_2); };

int Owner_006acd00::FUN_006acd00(int *param_2)
{
    int param_1 = (int)this;
    int *piVar1;
    int iVar2;

    iVar2 = (int)(0);
    if (0 < *(int *)(param_1 + 0x10)) {
        piVar1 = (int *)(*(int **)(param_1 + 4));
        do {
            if (((((char)piVar1[4] == (char)param_2[4]) && (*piVar1 == *param_2)) &&
                    (piVar1[1] == param_2[1])) && ((piVar1[2] == param_2[2] && (piVar1[3] == param_2[3])))) {
                return iVar2;
            }
            iVar2 = (int)(iVar2 + 1);
            piVar1 = (int *)(piVar1 + 5);
        } while (iVar2 < *(int *)(param_1 + 0x10));
    }
    return -1;
}

}  // namespace seed_006acd00
