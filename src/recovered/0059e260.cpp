// 0x0059e260: function not yet identified
//
// Body: 43 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_0059e260(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 )
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0059e260 {

struct Owner_0059e260 { void FUN_0059e260(undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5); };

void Owner_0059e260::FUN_0059e260(undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5)
{
    int param_1 = (int)this;
    *(undefined4 *)(param_1 + 0x2724) = param_2;
    *(undefined4 *)(param_1 + 0x2728) = param_3;
    *(undefined4 *)(param_1 + 0x272c) = param_4;
    *(undefined4 *)(param_1 + 0x2730) = param_5;
    return;
}

}  // namespace seed_0059e260
