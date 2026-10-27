// 0x004070d0: function not yet identified
//
// Body: 31 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_004070d0(int param_1,int param_2,uint param_3,undefined4 param_4)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004070d0 {

void __fastcall FUN_004070d0(int param_1, int param_2, uint param_3, undefined4 param_4)
{
    *(uint *)(param_1 + 0x10) = param_3;
    *(uint *)(param_1 + 0xc) = (uint)(param_2 << 0x10) / param_3;
    *(undefined4 *)(param_1 + 0x14) = param_4;
    return;
}

}  // namespace seed_004070d0
