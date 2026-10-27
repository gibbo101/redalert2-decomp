// 0x00659320: function not yet identified
//
// Body: 34 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __thiscall FUN_00659320(int param_1,undefined4 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00659320 {

extern undefined4  FUN_00783622(short *param_1, short *param_2, int param_3);

struct Owner_00659320 { void FUN_00659320(undefined4 param_2); };

void Owner_00659320::FUN_00659320(undefined4 param_2)
{
    int param_1 = (int)this;
    *(undefined2 *)(param_1 + 0x186) = 0;
    FUN_00783622((short *)(param_1 + 0x108), (short *)(param_2), (int)(0x3f));
    return;
}

}  // namespace seed_00659320
