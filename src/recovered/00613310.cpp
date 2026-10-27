// 0x00613310: function not yet identified
//
// Body: 31 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_00613310(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00613310 {

undefined4 __fastcall FUN_00613310(int param_1)
{
    if ((0 < *(int *)(param_1 + 0x14)) &&
          ((*(int *)(param_1 + 0x8c) == -1 || (0 < *(int *)(param_1 + 0x8c))))) {
        return 1;
    }
    return 0;
}

}  // namespace seed_00613310
