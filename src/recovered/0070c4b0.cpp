// 0x0070c4b0: function not yet identified
//
// Body: 20 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_0070c4b0(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0070c4b0 {

struct Owner_0070c4b0 { void FUN_0070c4b0(int param_2); };

void Owner_0070c4b0::FUN_0070c4b0(int param_2)
{
    int param_1 = (int)this;
    int *piVar1;

    if (param_2 < *(int *)(param_1 + 0x800)) {
        piVar1 = (int *)(param_1 + param_2 * 4);
        *piVar1 = *piVar1 + -1;
    }
    return;
}

}  // namespace seed_0070c4b0
