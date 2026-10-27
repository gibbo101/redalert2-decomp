// 0x006d4390: function not yet identified
//
// Body: 30 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __fastcall FUN_006d4390(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006d4390 {

undefined4 __fastcall FUN_006d4390(int param_1)
{
    int iVar1;

    iVar1 = (int)(*(int *)(param_1 + 0x98));
    if (((iVar1 != 2) && (iVar1 != 10)) && (iVar1 != 5)) {
        return 0;
    }
    return 1;
}

}  // namespace seed_006d4390
