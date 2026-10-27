// 0x006592f0: function not yet identified
//
// Body: 31 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __thiscall FUN_006592f0(int param_1,undefined4 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006592f0 {

extern undefined4  FUN_00783622(short *param_1, short *param_2, int param_3);

struct Owner_006592f0 { void FUN_006592f0(undefined4 param_2); };

void Owner_006592f0::FUN_006592f0(undefined4 param_2)
{
    int param_1 = (int)this;
    *(undefined2 *)(param_1 + 0x106) = 0;
    FUN_00783622((short *)(param_1 + 8), (short *)(param_2), (int)(0x7f));
    return;
}

}  // namespace seed_006592f0
