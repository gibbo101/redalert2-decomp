// 0x00783e4c: function not yet identified
//
// Body: 26 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: int FUN_00783e4c(int *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00783e4c {

int  FUN_00783e4c(int *param_1)
{
    int iVar1;
    int iVar2;

    iVar2 = (int)param_1 - *(int *)(*(int *)(*param_1 + -4) + 4);
    iVar1 = (int)(*(int *)(*(int *)(*param_1 + -4) + 8));
    if (iVar1 != 0) {
        iVar2 = (int)(iVar2 + *(int *)((int)param_1 - iVar1));
    }
    return iVar2;
}

}  // namespace seed_00783e4c
