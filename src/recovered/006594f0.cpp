// 0x006594f0: function not yet identified
//
// Body: 24 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_006594f0(int param_1,undefined4 *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006594f0 {

struct Owner_006594f0 { void FUN_006594f0(undefined4 *param_2); };

void Owner_006594f0::FUN_006594f0(undefined4 *param_2)
{
    int param_1 = (int)this;
    *param_2 = *(undefined4 *)(param_1 + 1000);
    param_2[1] = *(undefined4 *)(param_1 + 0x3ec);
    return;
}

}  // namespace seed_006594f0
