// 0x00796e52: function not yet identified
//
// Body: 26 bytes (frozen inventory bound).
// Referenced from 4 sites (unconditional call).
// Ghidra prototype: void FUN_00796e52(undefined4 param_1,int *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00796e52 {

extern undefined4  FUN_0079739d(byte param_1);

void  FUN_00796e52(undefined4 param_1, int *param_2)
{
    int iVar1;

    iVar1 = (int)(FUN_0079739d((byte)(param_1)));
    if (iVar1 == -1) {
        *param_2 = -1;
        return;
    }
    *param_2 = *param_2 + 1;
    return;
}

}  // namespace seed_00796e52
