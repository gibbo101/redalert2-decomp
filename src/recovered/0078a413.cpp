// 0x0078a413: function not yet identified
//
// Body: 23 bytes (frozen inventory bound).
// Referenced from 10 sites (unconditional call).
// Ghidra prototype: void FUN_0078a413(int param_1,undefined4 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078a413 {

extern undefined4  FUN_00792448(uint param_1, int *param_2);

void  FUN_0078a413(int param_1, undefined4 param_2)
{
    if (param_1 != -1) {
        FUN_00792448((uint)(param_1), (int *)(param_2));
    }
    return;
}

}  // namespace seed_0078a413
