// 0x00675300: function not yet identified
//
// Body: 24 bytes (frozen inventory bound).
// Referenced from 7 sites (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_00675300(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order, return width) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_00675300 {

bool __fastcall FUN_00675300(int param_1)
{
    if (*(int *)(param_1 + 0x38) != 0) {
        *(undefined1 *)(param_1 + 0x34) = 0;
        *(undefined4 *)(param_1 + 0x3c) = 0;
        *(undefined4 *)(param_1 + 0x38) = 0;
        return 1;
    }
    return 0;
}

}  // namespace seed_00675300
