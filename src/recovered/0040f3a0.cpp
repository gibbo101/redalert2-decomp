// 0x0040f3a0: function not yet identified
//
// Body: 28 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: int __fastcall FUN_0040f3a0(uint param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0040f3a0 {

extern "C" undefined4 DAT_00839b04;
extern "C" undefined4 DAT_00839b10;

int __fastcall FUN_0040f3a0(uint param_1)
{
    if ((param_1 != 0xffffffff) && (param_1 < DAT_00839b10)) {
        return *(int *)(DAT_00839b04 + param_1 * 4) + 0x24;
    }
    return 0;
}

}  // namespace seed_0040f3a0
