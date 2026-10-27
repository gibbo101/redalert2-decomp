// 0x005b4bd0: function not yet identified
//
// Body: 110 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 * __fastcall FUN_005b4bd0(undefined4 *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005b4bd0 {

undefined4 * __fastcall FUN_005b4bd0(undefined4 *param_1)
{
    int iVar1;
    undefined4 *puVar2;

    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[5] = 0;
    *(undefined1 *)(param_1 + 6) = 0;
    *(undefined1 *)((int)param_1 + 0x19) = 0;
    *(undefined1 *)((int)param_1 + 0x1a) = 0;
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[9] = 0;
    param_1[0xac] = 0;
    param_1[0xad] = 0;
    *(undefined2 *)(param_1 + 0xae) = 0;
    param_1[0xaf] = 0;
    param_1[0xb0] = 0;
    param_1[0xb1] = 0;
    *(undefined2 *)(param_1 + 10) = 0;
    *(undefined2 *)(param_1 + 0x5b) = 0;
    puVar2 = (undefined4 *)(param_1 + 0x520);
    for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar2 = 0x10001;
        puVar2 = (undefined4 *)(puVar2 + 1);
    }
    return param_1;
}

}  // namespace seed_005b4bd0
