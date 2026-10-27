// 0x0077c920: function not yet identified
//
// Body: 44 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_0077c920(int param_1,uint *param_2,uint *param_3,uint *param_4)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0077c920 {

undefined4 __fastcall FUN_0077c920(int param_1, uint *param_2, uint *param_3, uint *param_4)
{
    *param_2 = (uint)*(byte *)(param_1 + 0xf2);
    *param_3 = (uint)*(byte *)(param_1 + 0xf3);
    *param_4 = (uint)*(byte *)(param_1 + 0x108);
    return 0xffffffff;
}

}  // namespace seed_0077c920
