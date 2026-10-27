// 0x004318c0: function not yet identified
//
// Body: 13 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __thiscall FUN_004318c0(int param_1,undefined4 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004318c0 {

struct Owner_004318c0 { undefined4 FUN_004318c0(undefined4 param_2); };

undefined4 Owner_004318c0::FUN_004318c0(undefined4 param_2)
{
    int param_1 = (int)this;
    undefined4 uVar1;

    uVar1 = (undefined4)(*(undefined4 *)(param_1 + 0x28));
    *(undefined4 *)(param_1 + 0x28) = param_2;
    return uVar1;
}

}  // namespace seed_004318c0
