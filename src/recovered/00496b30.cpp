// 0x00496b30: function not yet identified
//
// Body: 19 bytes (frozen inventory bound).
// Referenced from 12 sites (unconditional call).
// Ghidra prototype: undefined1 __fastcall FUN_00496b30(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00496b30 {

undefined1 __fastcall FUN_00496b30(int param_1)
{
    undefined1 uVar1;

    if ((*(char *)(param_1 + 0x18) != '\0') || (uVar1 = 1, *(char *)(param_1 + 0x19) != '\x01')) {
        uVar1 = (undefined1)(0);
    }
    return uVar1;
}

}  // namespace seed_00496b30
