// 0x00782dfd: function not yet identified
//
// Body: 11 bytes (frozen inventory bound).
// Referenced from 74 sites (unconditional call).
// Ghidra prototype: void FUN_00782dfd(undefined4 param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00782dfd {

extern undefined4  FUN_00782d72(byte *param_1);

void  FUN_00782dfd(undefined4 param_1)
{
    FUN_00782d72((byte *)(param_1));
    return;
}

}  // namespace seed_00782dfd
