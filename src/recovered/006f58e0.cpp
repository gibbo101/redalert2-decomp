// 0x006f58e0: function not yet identified
//
// Body: 58 bytes (frozen inventory bound).
// Referenced from 25 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_006f58e0(undefined4 param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006f58e0 {

struct Callee_005b4da0 { undefined4 FUN_005b4da0(int, int, int, int, int, int, int); };
extern "C" undefined4 DAT_00a35db4;
extern "C" undefined4 DAT_00a3dc70;

void __fastcall FUN_006f58e0(undefined4 param_1, int param_2)
{
    undefined4 uVar1;

    if (param_2 == -1) {
        param_2 = (int)(0xf0);
    }
    uVar1 = (undefined4)(3);
    if (DAT_00a35db4 != 0) {
        uVar1 = (undefined4)(*(undefined4 *)(DAT_00a35db4 + 0x15f40));
    }
    ((Callee_005b4da0*)(&DAT_00a3dc70))->FUN_005b4da0((int)(0), (int)(0), (int)(param_1), (int)(uVar1), (int)(0x4046), (int)(param_2), (int)(1));
    return;
}

}  // namespace seed_006f58e0
