// 0x00406330: function not yet identified
//
// Body: 25 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __fastcall FUN_00406330(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00406330 {

undefined4 __fastcall FUN_00406330(int param_1)
{
    if (((*(byte *)(*(int *)(param_1 + 0x24) + 0x10) & 1) != 0) &&
          (*(int *)(*(int *)(param_1 + 0x24) + 0x4c) == 0)) {
        return 1;
    }
    return 0;
}

}  // namespace seed_00406330
