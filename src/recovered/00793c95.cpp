// 0x00793c95: function not yet identified
//
// Body: 17 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void FUN_00793c95(undefined4 param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00793c95 {

extern undefined4  FUN_00793cde(byte param_1, uint param_2, byte param_3);

void  FUN_00793c95(undefined4 param_1)
{
    FUN_00793cde((byte)(param_1), (uint)(0), (byte)(4));
    return;
}

}  // namespace seed_00793c95
