// 0x005818a0: function not yet identified
//
// Body: 49 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: undefined4 FUN_005818a0(short *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005818a0 {

extern "C" undefined4 DAT_0084e804;
extern "C" undefined4 DAT_00a70a24;

undefined4 __stdcall FUN_005818a0(short *param_1)
{
    if (DAT_00a70a24 == 0) {
        return 0xffffffff;
    }
    return *(undefined4 *)((param_1[1] * DAT_0084e804 + (int)*param_1) * 0x50 + 0x38 + DAT_00a70a24);
}

}  // namespace seed_005818a0
