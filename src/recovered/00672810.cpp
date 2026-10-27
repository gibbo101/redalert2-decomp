// 0x00672810: function not yet identified
//
// Body: 30 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_00672810(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00672810 {

void __fastcall FUN_00672810(int param_1)
{
    undefined4 *puVar1;
    int iVar2;

    *(undefined4 *)(param_1 + 0x24) = 0;
    puVar1 = (undefined4 *)(param_1 + 0x6c);
    iVar2 = (int)(8);
    do {
        puVar1[-8] = 0xffffffff;
        *puVar1 = 0xffffffff;
        puVar1 = (undefined4 *)(puVar1 + 1);
        iVar2 = (int)(iVar2 + -1);
    } while (iVar2 != 0);
    return;
}

}  // namespace seed_00672810
