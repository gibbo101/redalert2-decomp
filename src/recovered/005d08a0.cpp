// 0x005d08a0: function not yet identified
//
// Body: 17 bytes (frozen inventory bound).
// Referenced from 21 sites (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_005d08a0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005d08a0 {

undefined4 __fastcall FUN_005d08a0(int param_1)
{
    if (*(int *)(param_1 + 0x38) != 0) {
        return *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x38) + 4) + 0x28);
    }
    return 0;
}

}  // namespace seed_005d08a0
