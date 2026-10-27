// 0x005d8800: function not yet identified
//
// Body: 49 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: uint __fastcall FUN_005d8800(uint param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005d8800 {

uint __fastcall FUN_005d8800(uint param_1)
{
    uint uVar1;

    uVar1 = (uint)(0);
    if ((param_1 & 0x400) != 0) {
        uVar1 = (uint)(4);
    }
    if ((param_1 & 0x200) != 0) {
        uVar1 = (uint)(uVar1 | 2);
    }
    if ((param_1 & 0x100) != 0) {
        uVar1 = (uint)(uVar1 | 1);
    }
    if ((param_1 & 0x1000) != 0) {
        uVar1 = (uint)(uVar1 | 8);
    }
    return param_1 & 0xff | uVar1 << 8;
}

}  // namespace seed_005d8800
