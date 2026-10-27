// 0x005baf20: function not yet identified
//
// Body: 42 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: int FUN_005baf20(byte param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005baf20 {

int __stdcall FUN_005baf20(byte param_1)
{
    int iVar1;

    iVar1 = (int)(2);
    if ((param_1 & 1) != 0) {
        iVar1 = (int)(3);
    }
    if ((param_1 & 2) != 0) {
        iVar1 = (int)(iVar1 + 1);
    }
    if ((param_1 & 4) != 0) {
        iVar1 = (int)(iVar1 + 1);
    }
    if ((param_1 & 0x20) != 0) {
        iVar1 = (int)(iVar1 + 5);
    }
    return iVar1;
}

}  // namespace seed_005baf20
