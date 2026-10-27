// 0x0068a650: function not yet identified
//
// Body: 36 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: int __fastcall FUN_0068a650(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0068a650 {

int __fastcall FUN_0068a650(int param_1)
{
    int iVar1;
    int *piVar2;
    int iVar3;

    iVar3 = (int)(*(int *)(param_1 + 0x48));
    iVar1 = (int)(0);
    if (0 < iVar3) {
        piVar2 = (int *)(*(int **)(param_1 + 0x3c));
        do {
            if ((*(int *)(*piVar2 + 4) == 6) || (*(int *)(*piVar2 + 4) == 0)) {
                iVar1 = (int)(iVar1 + 1);
            }
            piVar2 = (int *)(piVar2 + 1);
            iVar3 = (int)(iVar3 + -1);
        } while (iVar3 != 0);
    }
    return iVar1;
}

}  // namespace seed_0068a650
