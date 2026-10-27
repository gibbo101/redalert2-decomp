// 0x006b0540: function not yet identified
//
// Body: 22 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __thiscall FUN_006b0540(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order, return width) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_006b0540 {

struct Owner_006b0540 { bool FUN_006b0540(int param_2, int unused_1, int unused_2, int unused_3); };

bool Owner_006b0540::FUN_006b0540(int param_2, int unused_1, int unused_2, int unused_3)
{
    int param_1 = (int)this;
    if (param_2 != 0) {
        *(undefined4 *)(param_2 + 0x541c) = *(undefined4 *)(param_1 + 0x74);
    }
    return 1;
}

}  // namespace seed_006b0540
