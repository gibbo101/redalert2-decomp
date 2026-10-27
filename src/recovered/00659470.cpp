// 0x00659470: function not yet identified
//
// Body: 24 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_00659470(int param_1,undefined4 *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00659470 {

struct Owner_00659470 { void FUN_00659470(undefined4 *param_2); };

void Owner_00659470::FUN_00659470(undefined4 *param_2)
{
    int param_1 = (int)this;
    *param_2 = *(undefined4 *)(param_1 + 0x3d8);
    param_2[1] = *(undefined4 *)(param_1 + 0x3dc);
    return;
}

}  // namespace seed_00659470
