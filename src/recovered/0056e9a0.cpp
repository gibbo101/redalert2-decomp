// 0x0056e9a0: function not yet identified
//
// Body: 41 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_0056e9a0(short *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0056e9a0 {

extern "C" undefined4 DAT_0084e804;
extern "C" undefined4 DAT_00a70a24;

undefined4 __fastcall FUN_0056e9a0(short *param_1)
{
    if (DAT_00a70a24 == 0) {
        return 0xffffffff;
    }
    return *(undefined4 *)((param_1[1] * DAT_0084e804 + (int)*param_1) * 0x50 + 0x38 + DAT_00a70a24);
}

}  // namespace seed_0056e9a0
