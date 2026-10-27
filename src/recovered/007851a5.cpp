// 0x007851a5: function not yet identified
//
// Body: 53 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: uint FUN_007851a5(byte param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_007851a5 {

uint  FUN_007851a5(byte param_1)
{
    uint uVar1;

    uVar1 = (uint)(0);
    if ((param_1 & 1) != 0) {
        uVar1 = (uint)(0x10);
    }
    if ((param_1 & 4) != 0) {
        uVar1 = (uint)(uVar1 | 8);
    }
    if ((param_1 & 8) != 0) {
        uVar1 = (uint)(uVar1 | 4);
    }
    if ((param_1 & 0x10) != 0) {
        uVar1 = (uint)(uVar1 | 2);
    }
    if ((param_1 & 0x20) != 0) {
        uVar1 = (uint)(uVar1 | 1);
    }
    if ((param_1 & 2) != 0) {
        uVar1 = (uint)(uVar1 | 0x80000);
    }
    return uVar1;
}

}  // namespace seed_007851a5
