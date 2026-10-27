// 0x0079042c: function not yet identified
//
// Body: 45 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void FUN_0079042c(undefined4 param_1,undefined4 param_2)
// Callees with accepted source:
//   FUN_00790341 -> src/recovered/00790341.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0079042c {

extern void  FUN_00790341(undefined4 param_1, undefined4 param_2);
extern undefined4  FUN_00791dc8(ushort *param_1, undefined4 *param_2, byte *param_3, undefined4 param_4, int param_5, int param_6, int param_7);

void  FUN_0079042c(undefined4 param_1, undefined4 param_2)
{
    undefined1 local_10 [12];

    FUN_00791dc8((ushort *)(local_10), (undefined4 *)(&param_2), (byte *)(param_2), (undefined4)(0), (int)(0), (int)(0), (int)(0));
    FUN_00790341((undefined4)(local_10), (undefined4)(param_1));
    return;
}

}  // namespace seed_0079042c
