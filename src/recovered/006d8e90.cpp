// 0x006d8e90: function not yet identified
//
// Body: 22 bytes (frozen inventory bound).
// Referenced from 6 sites (data).
// Ghidra prototype: undefined4 __fastcall FUN_006d8e90(int *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006d8e90 {

undefined4 __fastcall FUN_006d8e90(int *param_1)
{
    int iVar1;

    iVar1 = (int)((**(code **)(*param_1 + 0x80))());
    if (iVar1 != 0) {
        return *(undefined4 *)(iVar1 + 0x5a0);
    }
    return 0;
}

}  // namespace seed_006d8e90
