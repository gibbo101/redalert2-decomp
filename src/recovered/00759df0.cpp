// 0x00759df0: function not yet identified
//
// Body: 39 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_00759df0(undefined4 param_1,undefined4 param_2,undefined4 param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00759df0 {

extern undefined4  FUN_0078387f(undefined4 *param_1);
extern "C" undefined4 DAT_00b26898;
extern "C" undefined4 DAT_00b2a8a4;
extern "C" undefined4 DAT_00b2ab88;
extern "C" undefined4 DAT_00b2ac2c;

void __fastcall FUN_00759df0(undefined4 param_1, undefined4 param_2, undefined4 param_3)
{
    DAT_00b2ac2c = param_3;
    DAT_00b26898 = param_1;
    DAT_00b2ab88 = param_2;
    DAT_00b2a8a4 = FUN_0078387f((undefined4 *)(0));
    return;
}

}  // namespace seed_00759df0
