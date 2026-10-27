// 0x004b25c0: function not yet identified
//
// Body: 19 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_004b25c0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004b25c0 {

void __fastcall FUN_004b25c0(int param_1)
{
    if (*(int *)(param_1 + 0x20) != 0) {
        *(undefined4 *)(*(int *)(param_1 + 0x20) + 0x5c4) = 0;
        *(undefined4 *)(param_1 + 0x20) = 0;
    }
    return;
}

}  // namespace seed_004b25c0
