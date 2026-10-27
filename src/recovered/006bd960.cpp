// 0x006bd960: function not yet identified
//
// Body: 48 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_006bd960(int param_1,int param_2,char param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006bd960 {

struct Owner_006bd960 { void FUN_006bd960(int param_2, char param_3); };

void Owner_006bd960::FUN_006bd960(int param_2, char param_3)
{
    int param_1 = (int)this;
    undefined4 uVar1;
    int iVar2;

    if (param_3 != '\0') {
        uVar1 = (undefined4)(*(undefined4 *)(param_2 + 4));
        for (iVar2 = *(int *)(param_1 + 0x54); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x4c8)) {
            *(undefined4 *)(iVar2 + 0xd8) = uVar1;
        }
        *(undefined1 *)(param_1 + 0x80) = 1;
    }
    return;
}

}  // namespace seed_006bd960
