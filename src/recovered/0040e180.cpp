// 0x0040e180: function not yet identified
//
// Body: 75 bytes (frozen inventory bound).
// Referenced from 25 sites (unconditional call).
// Ghidra prototype: void __thiscall FUN_0040e180(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0040e180 {

struct Owner_0040e180 { void FUN_0040e180(int param_2); };

void Owner_0040e180::FUN_0040e180(int param_2)
{
    int param_1 = (int)this;
    undefined4 uVar1;

    if (((param_2 != 0) && (*(int *)(param_2 + 4) != 0)) && (*(int *)(param_2 + 8) != 0)) {
        *(int *)(*(int *)(param_2 + 8) + 4) = *(int *)(param_2 + 4);
        *(undefined4 *)(*(int *)(param_2 + 4) + 8) = *(undefined4 *)(param_2 + 8);
        *(undefined4 *)(param_2 + 8) = 0;
        *(undefined4 *)(param_2 + 4) = 0;
    }
    uVar1 = (undefined4)(*(undefined4 *)(param_1 + 4));
    *(int *)(param_2 + 8) = param_1;
    *(undefined4 *)(param_2 + 4) = uVar1;
    if (*(int *)(param_1 + 4) != 0) {
        *(int *)(*(int *)(param_1 + 4) + 8) = param_2;
    }
    *(int *)(param_1 + 4) = param_2;
    return;
}

}  // namespace seed_0040e180
