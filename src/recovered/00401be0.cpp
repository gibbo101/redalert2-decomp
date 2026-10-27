// 0x00401be0: function not yet identified
//
// Body: 22 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_00401be0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00401be0 {

void __fastcall FUN_00401be0(int param_1)
{
    undefined4 *puVar1;

    for (puVar1 = *(undefined4 **)(param_1 + 0xc); puVar1 != (undefined4 *)(param_1 + 0xc);
            puVar1 = (undefined4 *)*puVar1) {
        puVar1[6] = 0;
    }
    return;
}

}  // namespace seed_00401be0
