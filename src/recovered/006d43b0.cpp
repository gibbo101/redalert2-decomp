// 0x006d43b0: function not yet identified
//
// Body: 74 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __fastcall FUN_006d43b0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006d43b0 {

undefined4 __fastcall FUN_006d43b0(int param_1)
{
    int iVar1;

    iVar1 = (int)(*(int *)(param_1 + 0x98));
    if (((((iVar1 != 0) && (iVar1 != 7)) && (iVar1 != 0xd)) &&
            ((((iVar1 != 0xe && (iVar1 != 0x10)) &&
                ((iVar1 != 0x12 && ((iVar1 != 0x13 && (iVar1 != 0x14)))))) && (iVar1 != 0x16)))) &&
          (((iVar1 != 0x17 && (iVar1 != 0x1c)) && (iVar1 != 0x18)))) {
        return 0;
    }
    return 1;
}

}  // namespace seed_006d43b0
