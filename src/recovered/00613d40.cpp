// 0x00613d40: function not yet identified
//
// Body: 30 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_00613d40(int param_1,undefined4 param_2,undefined4 param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00613d40 {

struct Owner_00613d40 { void FUN_00613d40(undefined4 param_2, undefined4 param_3); };

void Owner_00613d40::FUN_00613d40(undefined4 param_2, undefined4 param_3)
{
    int param_1 = (int)this;
    *(undefined4 *)(param_1 + 0x90) = param_2;
    *(undefined4 *)(param_1 + 0x94) = param_3;
    *(undefined1 *)(param_1 + 0x98) = 1;
    return;
}

}  // namespace seed_00613d40
