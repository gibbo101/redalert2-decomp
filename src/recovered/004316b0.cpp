// 0x004316b0: function not yet identified
//
// Body: 88 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __thiscall FUN_004316b0(int param_1,undefined4 param_2,undefined4 param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004316b0 {

struct Callee_004314b0 { undefined4 FUN_004314b0(ushort *param_2, int *param_3, int *param_4, int param_5); };

struct Owner_004316b0 { undefined4 FUN_004316b0(undefined4 param_2, undefined4 param_3); };

undefined4 Owner_004316b0::FUN_004316b0(undefined4 param_2, undefined4 param_3)
{
    int param_1 = (int)this;
    if (*(char *)(param_1 + 0x40) != '\0') {
        *(undefined4 *)(param_1 + 0x2c) = 2;
        ((Callee_004314b0*)(param_1))->FUN_004314b0((ushort *)(param_2), (int *)(&param_3), (int *)(0), (int)(param_3));
        *(undefined4 *)(param_1 + 0x2c) = 1;
        return param_3;
    }
    ((Callee_004314b0*)(param_1))->FUN_004314b0((ushort *)(param_2), (int *)(&param_3), (int *)(0), (int)(param_3));
    return param_3;
}

}  // namespace seed_004316b0
