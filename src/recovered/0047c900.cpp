// 0x0047c900: function not yet identified
//
// Body: 39 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __fastcall FUN_0047c900(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0047c900 {

void __fastcall FUN_0047c900(int param_1)
{
    *(uint *)(param_1 + 300) = *(uint *)(param_1 + 300) | 0x18;
    if (0 < *(int *)(param_1 + 0x130)) {
        *(uint *)(param_1 + 0x140) = *(uint *)(param_1 + 0x140) | 0x20;
    }
    return;
}

}  // namespace seed_0047c900
