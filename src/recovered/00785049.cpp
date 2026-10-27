// 0x00785049: function not yet identified
//
// Body: 22 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void FUN_00785049(undefined4 param_1,uint param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00785049 {

extern undefined4  FUN_00785014(uint param_1, uint param_2);

void  FUN_00785049(undefined4 param_1, uint param_2)
{
    FUN_00785014((uint)(param_1), (uint)(param_2 & 0xfff7ffff));
    return;
}

}  // namespace seed_00785049
