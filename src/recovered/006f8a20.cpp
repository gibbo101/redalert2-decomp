// 0x006f8a20: function not yet identified
//
// Body: 45 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_006f8a20(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006f8a20 {

extern "C" undefined4 DAT_00ac1334;
extern "C" undefined4 DAT_00ac1338;

void __fastcall FUN_006f8a20(int param_1)
{
    if (param_1 == 0) {
        DAT_00ac1334 = 0;
        DAT_00ac1338 = 0;
        return;
    }
    if (param_1 == DAT_00ac1334) {
        DAT_00ac1334 = 0;
        return;
    }
    if (param_1 == DAT_00ac1338) {
        DAT_00ac1338 = 0;
    }
    return;
}

}  // namespace seed_006f8a20
