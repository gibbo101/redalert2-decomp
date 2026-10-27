// 0x0074dd20: function not yet identified
//
// Body: 35 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_0074dd20(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_0074dd20 {

extern "C" undefined4 DAT_007fd324;
extern "C" int DAT_00a3fa8c;
extern "C" undefined4 DAT_00b26a2c;

void __fastcall FUN_0074dd20(int param_1, int param_2)
{
    if (param_1 < DAT_00a3fa8c) {
        if ((int)(&DAT_00b26a2c)[param_1] < (int)(&DAT_007fd324)[param_1]) {
            (&DAT_00b26a2c)[param_1] = param_2;
        }
    }
    return;
}

}  // namespace seed_0074dd20
