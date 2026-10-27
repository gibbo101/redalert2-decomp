// 0x005c93d0: function not yet identified
//
// Body: 44 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __fastcall FUN_005c93d0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005c93d0 {

extern "C" undefined4 DAT_00a72d34;
extern "C" undefined4 DAT_00a72d38;
extern "C" undefined4 DAT_00a72d3c;

undefined4 __fastcall FUN_005c93d0(int param_1)
{
    undefined4 uVar1;

    uVar1 = (undefined4)(0xffffffff);
    if (param_1 == DAT_00a72d34) {
        return 2;
    }
    if (param_1 == DAT_00a72d38) {
        return 1;
    }
    if (param_1 == DAT_00a72d3c) {
        uVar1 = (undefined4)(0);
    }
    return uVar1;
}

}  // namespace seed_005c93d0
