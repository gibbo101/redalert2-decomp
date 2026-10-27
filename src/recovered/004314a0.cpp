// 0x004314a0: function not yet identified
//
// Body: 13 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined1 __thiscall FUN_004314a0(int param_1,undefined1 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004314a0 {

struct Owner_004314a0 { undefined1 FUN_004314a0(undefined1 param_2); };

undefined1 Owner_004314a0::FUN_004314a0(undefined1 param_2)
{
    int param_1 = (int)this;
    undefined1 uVar1;

    uVar1 = (undefined1)(*(undefined1 *)(param_1 + 0x40));
    *(undefined1 *)(param_1 + 0x40) = param_2;
    return uVar1;
}

}  // namespace seed_004314a0
