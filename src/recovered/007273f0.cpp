// 0x007273f0: function not yet identified
//
// Body: 14 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_007273f0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_007273f0 {

undefined4 __fastcall FUN_007273f0(int param_1)
{
    if (*(int *)(param_1 + 0xc) != 0) {
        return *(undefined4 *)(*(int *)(param_1 + 0xc) + 8);
    }
    return 0;
}

}  // namespace seed_007273f0
