// 0x006bd990: function not yet identified
//
// Body: 30 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __thiscall FUN_006bd990(int param_1,undefined4 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006bd990 {

struct Owner_006bd990 { void FUN_006bd990(undefined4 param_2); };

void Owner_006bd990::FUN_006bd990(undefined4 param_2)
{
    int param_1 = (int)this;
    int iVar1;

    for (iVar1 = *(int *)(param_1 + 0x54); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x4c8)) {
        *(undefined4 *)(iVar1 + 0xd8) = param_2;
    }
    return;
}

}  // namespace seed_006bd990
