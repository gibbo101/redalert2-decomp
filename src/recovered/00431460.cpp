// 0x00431460: function not yet identified
//
// Body: 51 bytes (frozen inventory bound).
// Referenced from 10 sites (unconditional call).
// Ghidra prototype: void __thiscall FUN_00431460(int param_1,undefined4 *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00431460 {

struct Owner_00431460 { void FUN_00431460(undefined4 *param_2); };

void Owner_00431460::FUN_00431460(undefined4 *param_2)
{
    int param_1 = (int)this;
    if (param_2 != (undefined4 *)0x0) {
        *(undefined4 *)(param_1 + 0x30) = *param_2;
        *(undefined4 *)(param_1 + 0x34) = param_2[1];
        *(undefined4 *)(param_1 + 0x38) = param_2[2];
        *(undefined4 *)(param_1 + 0x3c) = param_2[3];
        return;
    }
    *(undefined4 *)(param_1 + 0x3c) = 0;
    *(undefined4 *)(param_1 + 0x38) = 0;
    *(undefined4 *)(param_1 + 0x34) = 0;
    *(undefined4 *)(param_1 + 0x30) = 0;
    return;
}

}  // namespace seed_00431460
