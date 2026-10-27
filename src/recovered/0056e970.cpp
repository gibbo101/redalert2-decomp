// 0x0056e970: function not yet identified
//
// Body: 39 bytes (frozen inventory bound).
// Referenced from 33 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_0056e970(short *param_1,undefined4 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0056e970 {

extern "C" undefined4 DAT_0084e804;
extern "C" undefined4 DAT_00a70a24;

void __fastcall FUN_0056e970(short *param_1, undefined4 param_2)
{
    if (DAT_00a70a24 != 0) {
        *(undefined4 *)((param_1[1] * DAT_0084e804 + (int)*param_1) * 0x50 + 0x38 + DAT_00a70a24) =
                  param_2;
    }
    return;
}

}  // namespace seed_0056e970
