// 0x00784bb8: function not yet identified
//
// Body: 23 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: void FUN_00784bb8(undefined4 param_1,undefined4 param_2,undefined4 param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00784bb8 {

extern undefined4  FUN_00784bcf(ushort *param_1, undefined4 *param_2, uint param_3, uint param_4);

void  FUN_00784bb8(undefined4 param_1, undefined4 param_2, undefined4 param_3)
{
    FUN_00784bcf((ushort *)(param_1), (undefined4 *)(param_2), (uint)(param_3), (uint)(0));
    return;
}

}  // namespace seed_00784bb8
