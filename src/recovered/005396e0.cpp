// 0x005396e0: function not yet identified
//
// Body: 30 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __fastcall FUN_005396e0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005396e0 {

undefined4 __fastcall FUN_005396e0(int param_1)
{
    if ((*(int *)(param_1 + 4) == 0) &&
          (*(int *)(*(int *)(param_1 + 0xc) * 0x10 + 0x1c + param_1) == 0)) {
        return 1;
    }
    return 0;
}

}  // namespace seed_005396e0
