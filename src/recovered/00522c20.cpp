// 0x00522c20: function not yet identified
//
// Body: 33 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __fastcall FUN_00522c20(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_00522c20 {

extern "C" int DAT_00a521dc;
extern "C" undefined4 DAT_00a522b0;
extern "C" undefined4 DAT_00a522b4;

undefined4 __fastcall FUN_00522c20(int param_1)
{
    if (((DAT_00a522b0 != 0) && (param_1 >= 0)) && (param_1 < DAT_00a521dc)) {
        return *(undefined4 *)(DAT_00a522b4 + param_1 * 4);
    }
    return 0;
}

}  // namespace seed_00522c20
