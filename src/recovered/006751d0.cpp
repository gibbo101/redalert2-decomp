// 0x006751d0: function not yet identified
//
// Body: 10 bytes (frozen inventory bound).
// Referenced from 5 sites (unconditional call).
// Ghidra prototype: void __thiscall FUN_006751d0(int param_1,undefined1 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006751d0 {

struct Owner_006751d0 { void FUN_006751d0(undefined1 param_2); };

void Owner_006751d0::FUN_006751d0(undefined1 param_2)
{
    int param_1 = (int)this;
    *(undefined1 *)(param_1 + 0x5c) = param_2;
    return;
}

}  // namespace seed_006751d0
