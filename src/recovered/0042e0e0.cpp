// 0x0042e0e0: function not yet identified
//
// Body: 24 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 * __fastcall FUN_0042e0e0(undefined4 *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0042e0e0 {

undefined4 * __fastcall FUN_0042e0e0(undefined4 *param_1)
{
    int iVar1;
    undefined4 *puVar2;

    puVar2 = (undefined4 *)(param_1);
    for (iVar1 = 0x18; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar2 = 0;
        puVar2 = (undefined4 *)(puVar2 + 1);
    }
    param_1[0x18] = 0;
    param_1[0x1f] = 0;
    return param_1;
}

}  // namespace seed_0042e0e0
