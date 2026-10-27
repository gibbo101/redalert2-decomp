// 0x00406660: function not yet identified
//
// Body: 22 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_00406660(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00406660 {

undefined4 __fastcall FUN_00406660(int param_1)
{
    undefined4 uVar1;

    uVar1 = (undefined4)(1);
    if (((*(byte *)(param_1 + 0x10) & 1) == 0) || (*(int *)(param_1 + 0x4c) != 0)) {
        uVar1 = (undefined4)(0);
    }
    return uVar1;
}

}  // namespace seed_00406660
