// 0x0078ab9b: function not yet identified
//
// Body: 32 bytes (frozen inventory bound).
// Referenced from 4 sites (unconditional call).
// Ghidra prototype: void FUN_0078ab9b(undefined4 param_1,undefined4 param_2,int *param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078ab9b {

extern undefined4  FUN_0078b258(uint param_1, int *param_2);

void  FUN_0078ab9b(undefined4 param_1, undefined4 param_2, int *param_3)
{
    short sVar1;

    sVar1 = (short)(FUN_0078b258((uint)(param_1), (int *)(param_2)));
    if (sVar1 == -1) {
        *param_3 = -1;
        return;
    }
    *param_3 = *param_3 + 1;
    return;
}

}  // namespace seed_0078ab9b
