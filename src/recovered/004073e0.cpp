// 0x004073e0: function not yet identified
//
// Body: 19 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: int __fastcall FUN_004073e0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004073e0 {

int __fastcall FUN_004073e0(int param_1)
{
    int iVar1;

    iVar1 = (int)(*(int *)(param_1 + 4));
    if ((iVar1 == *(int *)(iVar1 + 8)) && (iVar1 = *(int *)(iVar1 + 4), iVar1 == *(int *)(iVar1 + 8)))
    {
        iVar1 = (int)(0);
    }
    return iVar1;
}

}  // namespace seed_004073e0
