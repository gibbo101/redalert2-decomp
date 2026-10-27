// 0x00479cc0: function not yet identified
//
// Body: 43 bytes (frozen inventory bound).
// Referenced from 16 sites (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_00479cc0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_00479cc0 {

extern "C" int DAT_008661d8;

undefined4 __fastcall FUN_00479cc0(int param_1)
{
    if (((*(short *)(param_1 + 0x116) >= 0) && (*(short *)(param_1 + 0x116) < DAT_008661d8)) &&
          (*(int *)(param_1 + 0xec) == 10)) {
        return 1;
    }
    return 0;
}

}  // namespace seed_00479cc0
