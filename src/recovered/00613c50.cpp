// 0x00613c50: function not yet identified
//
// Body: 16 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_00613c50(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00613c50 {

undefined4 __fastcall FUN_00613c50(int param_1)
{
    int iVar1;

    iVar1 = (int)(*(int *)(param_1 + 0x14) + -1);
    if (iVar1 < 0) {
        return 0;
    }
    return *(undefined4 *)(*(int *)(param_1 + 8) + iVar1 * 4);
}

}  // namespace seed_00613c50
