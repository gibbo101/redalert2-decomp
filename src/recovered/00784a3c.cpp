// 0x00784a3c: function not yet identified
//
// Body: 11 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void FUN_00784a3c(undefined4 param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00784a3c {

extern undefined4  FUN_00784a0b(undefined4 *param_1);

void  FUN_00784a3c(undefined4 param_1)
{
    FUN_00784a0b((undefined4 *)(param_1));
    return;
}

}  // namespace seed_00784a3c
