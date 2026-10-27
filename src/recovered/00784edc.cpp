// 0x00784edc: function not yet identified
//
// Body: 17 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void FUN_00784edc(undefined4 param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00784edc {

extern void  FUN_00784f1c(UINT param_1, int param_2, int param_3);

void  FUN_00784edc(undefined4 param_1)
{
    FUN_00784f1c((UINT)(param_1), (int)(0), (int)(0));
    return;
}

}  // namespace seed_00784edc
