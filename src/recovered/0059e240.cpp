// 0x0059e240: function not yet identified
//
// Body: 23 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void __thiscall FUN_0059e240(int param_1,undefined4 param_2,undefined4 param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0059e240 {

struct Owner_0059e240 { void FUN_0059e240(undefined4 param_2, undefined4 param_3); };

void Owner_0059e240::FUN_0059e240(undefined4 param_2, undefined4 param_3)
{
    int param_1 = (int)this;
    *(undefined4 *)(param_1 + 0x271c) = param_2;
    *(undefined4 *)(param_1 + 0x2720) = param_3;
    return;
}

}  // namespace seed_0059e240
