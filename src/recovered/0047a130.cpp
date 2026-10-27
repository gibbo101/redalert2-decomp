// 0x0047a130: function not yet identified
//
// Body: 38 bytes (frozen inventory bound).
// Referenced from 12 sites (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_0047a130(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_0047a130 {

extern "C" undefined4 DAT_008661cc;
extern "C" int DAT_008661d8;

undefined4 __fastcall FUN_0047a130(int param_1)
{
    short sVar1;

    sVar1 = (short)(*(short *)(param_1 + 0x116));
    if ((sVar1 >= 0) && (sVar1 < DAT_008661d8)) {
        return *(undefined4 *)(DAT_008661cc + sVar1 * 4);
    }
    return 0;
}

}  // namespace seed_0047a130
