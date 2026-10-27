// 0x00633110: function not yet identified
//
// Body: 26 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __fastcall FUN_00633110(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00633110 {

undefined4 __fastcall FUN_00633110(int param_1)
{
    undefined4 uVar1;

    uVar1 = (undefined4)(1);
    if ((*(int *)(param_1 + 0x14ac) != 1) || (*(int *)(param_1 + 0x14a8) != 1)) {
        uVar1 = (undefined4)(0);
    }
    return uVar1;
}

}  // namespace seed_00633110
