// 0x00595bc0: function not yet identified
//
// Body: 45 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __fastcall FUN_00595bc0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00595bc0 {

void __fastcall FUN_00595bc0(int param_1)
{
    if (((param_1 != 0) && (*(int *)(param_1 + 4) != 0)) && (*(int *)(param_1 + 8) != 0)) {
        *(int *)(*(int *)(param_1 + 8) + 4) = *(int *)(param_1 + 4);
        *(undefined4 *)(*(int *)(param_1 + 4) + 8) = *(undefined4 *)(param_1 + 8);
        *(undefined4 *)(param_1 + 8) = 0;
        *(undefined4 *)(param_1 + 4) = 0;
    }
    return;
}

}  // namespace seed_00595bc0
