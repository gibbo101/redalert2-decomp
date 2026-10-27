// 0x006f8a00: function not yet identified
//
// Body: 29 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __fastcall FUN_006f8a00(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006f8a00 {

extern "C" undefined4 DAT_00ac1334;
extern "C" undefined4 DAT_00ac1338;

void __fastcall FUN_006f8a00(int param_1)
{
    if (*(int *)(*(int *)(param_1 + 0x418) + 0xba0) == 5) {
        DAT_00ac1338 = param_1;
        return;
    }
    DAT_00ac1334 = param_1;
    return;
}

}  // namespace seed_006f8a00
