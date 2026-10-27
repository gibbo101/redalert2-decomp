// 0x0049ec40: function not yet identified
//
// Body: 23 bytes (frozen inventory bound).
// Referenced from 5 sites (unconditional call).
// Ghidra prototype: int __fastcall FUN_0049ec40(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0049ec40 {

int __fastcall FUN_0049ec40(int param_1)
{
    int iVar1;

    if ((*(char *)(param_1 + 0x1198) == '\0') || (iVar1 = *(int *)(param_1 + 0x119c), iVar1 == 0)) {
        iVar1 = (int)(0);
    }
    return iVar1;
}

}  // namespace seed_0049ec40
