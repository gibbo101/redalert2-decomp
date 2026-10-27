// 0x00784aa8: function not yet identified
//
// Body: 14 bytes (frozen inventory bound).
// Referenced from 11 sites (unconditional call).
// Ghidra prototype: void FUN_00784aa8(undefined4 param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00784aa8 {

extern undefined4  FUN_0078bbb0(ushort param_1, ushort param_2);

void  FUN_00784aa8(undefined4 param_1)
{
    FUN_0078bbb0((ushort)(param_1), (ushort)(8));
    return;
}

}  // namespace seed_00784aa8
