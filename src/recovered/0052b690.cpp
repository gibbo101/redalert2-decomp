// 0x0052b690: function not yet identified
//
// Body: 85 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: undefined4 __thiscall FUN_0052b690(int *param_1,int param_2,int *param_3,int *param_4)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order, return width) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_0052b690 {

struct Owner_0052b690 { bool FUN_0052b690(int param_2, int *param_3, int *param_4); };

bool Owner_0052b690::FUN_0052b690(int param_2, int *param_3, int *param_4)
{
    int * param_1 = (int *)this;
    int iVar1;
    int iVar2;
    int *piVar3;

    piVar3 = (int *)(**(code **)(*param_1 + 0x9c))();
    if (piVar3 != (int *)0x0) {
        iVar1 = (int)(piVar3[param_2 % (piVar3[1] * *piVar3) + 4]);
        *param_3 = piVar3[2];
        iVar2 = (int)(piVar3[3]);
        *param_4 = iVar2;
        if ((iVar1 != 0) && ((*(byte *)(iVar1 + 0x24) & 1) != 0)) {
            *param_4 = (*(int *)(iVar1 + 4) - *(int *)(iVar1 + 0x18)) + iVar2;
        }
        return 1;
    }
    return 0;
}

}  // namespace seed_0052b690
