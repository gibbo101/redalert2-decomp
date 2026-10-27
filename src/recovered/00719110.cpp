// 0x00719110: function not yet identified
//
// Body: 66 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_00719110(int param_1)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00719110 {

extern void  FUN_00781d3b(undefined4 param_1);

void __fastcall FUN_00719110(int param_1)
{
    if (*(int *)(param_1 + 0x10) != 0) {
        FUN_00781d3b((undefined4)(*(int *)(param_1 + 0x10)));
    }
    *(undefined4 *)(param_1 + 0x10) = 0;
    if (*(int *)(param_1 + 0x14) != 0) {
        FUN_00781d3b((undefined4)(*(int *)(param_1 + 0x14)));
    }
    *(undefined4 *)(param_1 + 0x14) = 0;
    if (*(int *)(param_1 + 0x18) != 0) {
        FUN_00781d3b((undefined4)(*(int *)(param_1 + 0x18)));
    }
    *(undefined4 *)(param_1 + 0x18) = 0;
    return;
}

}  // namespace seed_00719110
