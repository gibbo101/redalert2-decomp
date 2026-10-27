// 0x0070c4d0: function not yet identified
//
// Body: 49 bytes (frozen inventory bound).
// Referenced from 10 sites (unconditional call).
// Ghidra prototype: void __thiscall FUN_0070c4d0(undefined4 *param_1,undefined4 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0070c4d0 {

struct Owner_0070c4d0 { void FUN_0070c4d0(undefined4 param_2); };

void Owner_0070c4d0::FUN_0070c4d0(undefined4 param_2)
{
    undefined4 * param_1 = (undefined4 *)this;
    int iVar1;
    undefined4 *puVar2;

    param_1[0x200] = 0x200;
    iVar1 = (int)(0);
    puVar2 = (undefined4 *)(param_1);
    do {
        *puVar2 = 0;
        iVar1 = (int)(iVar1 + 1);
        puVar2 = (undefined4 *)(puVar2 + 1);
    } while (iVar1 < (int)param_1[0x200]);
    param_1[0x200] = param_2;
    return;
}

}  // namespace seed_0070c4d0
