// 0x004016b0: function not yet identified
//
// Body: 60 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_004016b0(int *param_1,int param_2,int param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004016b0 {

void __fastcall FUN_004016b0(int *param_1, int param_2, int param_3)
{
    int iVar1;
    undefined4 uVar2;

    iVar1 = (int)(*param_1 + param_2 * 0x24);
    uVar2 = (undefined4)(*(undefined4 *)(param_3 + 8));
    *(undefined4 *)(iVar1 + 0x1c) = 0;
    *(undefined4 *)(iVar1 + 0x18) = uVar2;
    if (*(int *)(param_3 + 0xc) == 2) {
        *(undefined4 *)(iVar1 + 0x1c) = 1;
    }
    if (*(int *)(param_3 + 0x10) == 2) {
        *(uint *)(iVar1 + 0x1c) = *(uint *)(iVar1 + 0x1c) | 4;
    }
    return;
}

}  // namespace seed_004016b0
