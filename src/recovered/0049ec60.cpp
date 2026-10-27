// 0x0049ec60: function not yet identified
//
// Body: 24 bytes (frozen inventory bound).
// Referenced from 5 sites (unconditional call).
// Ghidra prototype: void __thiscall FUN_0049ec60(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0049ec60 {

struct Owner_0049ec60 { void FUN_0049ec60(int param_2); };

void Owner_0049ec60::FUN_0049ec60(int param_2)
{
    int param_1 = (int)this;
    *(int *)(param_1 + 0x119c) = param_2;
    *(bool *)(param_1 + 0x1198) = param_2 != 0;
    return;
}

}  // namespace seed_0049ec60
