// 0x0047a270: function not yet identified
//
// Body: 29 bytes (frozen inventory bound).
// Referenced from 31 sites (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_0047a270(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_0047a270 {

extern "C" int DAT_00a52580;

undefined4 __fastcall FUN_0047a270(int param_1)
{
    if ((*(int *)(param_1 + 0x38) >= DAT_00a52580) && (*(int *)(param_1 + 0x38) < DAT_00a52580 + 0xe))
    {
        return 1;
    }
    return 0;
}

}  // namespace seed_0047a270
