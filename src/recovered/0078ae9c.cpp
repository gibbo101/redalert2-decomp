// 0x0078ae9c: function not yet identified
//
// Body: 42 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void FUN_0078ae9c(int param_1,undefined4 *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078ae9c {

extern undefined4  FUN_007843f9(int *param_1);

void  FUN_0078ae9c(int param_1, undefined4 *param_2)
{
    if ((param_1 != 0) && ((*(byte *)((int)param_2 + 0xd) & 0x10) != 0)) {
        FUN_007843f9((int *)(param_2));
        *(byte *)((int)param_2 + 0xd) = *(byte *)((int)param_2 + 0xd) & 0xee;
        param_2[6] = 0;
        *param_2 = 0;
        param_2[2] = 0;
    }
    return;
}

}  // namespace seed_0078ae9c
