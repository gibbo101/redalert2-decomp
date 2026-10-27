// 0x00613d20: function not yet identified
//
// Body: 21 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __fastcall FUN_00613d20(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00613d20 {

undefined4 __fastcall FUN_00613d20(int param_1)
{
    if (*(int *)(param_1 + 0x94) == -1) {
        return 0;
    }
    return *(undefined4 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x94) * 4);
}

}  // namespace seed_00613d20
