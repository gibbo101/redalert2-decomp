// 0x005ad8c0: function not yet identified
//
// Owner: MSOverlayAnim, virtual slot 7 (vtable +0x1c) (from RTTI/vtables).
// Body: 22 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 __fastcall FUN_005ad8c0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005ad8c0 {

undefined4 __fastcall FUN_005ad8c0(int param_1)
{
    if ((*(char *)(param_1 + 0xc) != '\0') && (*(uint *)(param_1 + 0x40) < 4)) {
        return 0;
    }
    return 1;
}

}  // namespace seed_005ad8c0
