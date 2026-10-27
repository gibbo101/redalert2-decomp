// 0x00613b70: function not yet identified
//
// Body: 15 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: int __fastcall FUN_00613b70(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00613b70 {

int __fastcall FUN_00613b70(int param_1)
{
    int iVar1;

    iVar1 = (int)(*(int *)(param_1 + 0x8c));
    if (iVar1 == -1) {
        iVar1 = (int)(*(int *)(param_1 + 0x14));
    }
    return iVar1;
}

}  // namespace seed_00613b70
