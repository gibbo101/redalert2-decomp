// 0x00672f20: function not yet identified
//
// Body: 39 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __thiscall FUN_00672f20(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00672f20 {

struct Owner_00672f20 { void FUN_00672f20(int param_2); };

void Owner_00672f20::FUN_00672f20(int param_2)
{
    int param_1 = (int)this;
    undefined2 *puVar1;

    if (param_2 < 7) {
        puVar1 = (undefined2 *)(param_1 + 0x3022 + param_2 * 2);
        param_2 = (int)(7 - param_2);
        do {
            *puVar1 = puVar1[1];
            puVar1 = (undefined2 *)(puVar1 + 1);
            param_2 = (int)(param_2 + -1);
        } while (param_2 != 0);
    }
    return;
}

}  // namespace seed_00672f20
