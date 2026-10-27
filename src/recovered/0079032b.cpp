// 0x0079032b: function not yet identified
//
// Body: 22 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void FUN_0079032b(undefined4 param_1,undefined4 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0079032b {

extern undefined4  FUN_007901bf(ushort *param_1, uint *param_2, int *param_3);
extern "C" undefined4 DAT_008300a0;

void  FUN_0079032b(undefined4 param_1, undefined4 param_2)
{
    FUN_007901bf((ushort *)(param_1), (uint *)(param_2), (int *)(&DAT_008300a0));
    return;
}

}  // namespace seed_0079032b
