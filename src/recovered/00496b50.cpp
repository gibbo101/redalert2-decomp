// 0x00496b50: function not yet identified
//
// Body: 20 bytes (frozen inventory bound).
// Referenced from 13 sites (unconditional call).
// Ghidra prototype: undefined1 __fastcall FUN_00496b50(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00496b50 {

undefined1 __fastcall FUN_00496b50(int param_1)
{
    if ((*(char *)(param_1 + 0x18) == '\0') && (*(char *)(param_1 + 0x19) == '\0')) {
        return 1;
    }
    return 0;
}

}  // namespace seed_00496b50
