// 0x00431860: function not yet identified
//
// Body: 86 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_00431860(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 )
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00431860 {

struct Callee_004314b0 { undefined4 FUN_004314b0(ushort *param_2, int *param_3, int *param_4, int param_5); };

struct Owner_00431860 { void FUN_00431860(undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5); };

void Owner_00431860::FUN_00431860(undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5)
{
    int param_1 = (int)this;
    if (*(char *)(param_1 + 0x40) != '\0') {
        *(undefined4 *)(param_1 + 0x2c) = 2;
        ((Callee_004314b0*)(param_1))->FUN_004314b0((ushort *)(param_2), (int *)(param_3), (int *)(param_4), (int)(param_5));
        *(undefined4 *)(param_1 + 0x2c) = 1;
        return;
    }
    ((Callee_004314b0*)(param_1))->FUN_004314b0((ushort *)(param_2), (int *)(param_3), (int *)(param_4), (int)(param_5));
    return;
}

}  // namespace seed_00431860
