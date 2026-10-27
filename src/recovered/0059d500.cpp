// 0x0059d500: function not yet identified
//
// Body: 140 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional jump).
// Ghidra prototype: void __fastcall FUN_0059d500(int *param_1)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0059d500 {

extern void  FUN_00781d3b(undefined4 param_1);

void __fastcall FUN_0059d500(int *param_1)
{
    if (*param_1 != 0) {
        FUN_00781d3b((undefined4)(*param_1));
        *param_1 = 0;
    }
    if (param_1[1] != 0) {
        FUN_00781d3b((undefined4)(param_1[1]));
        param_1[1] = 0;
    }
    if (param_1[2] != 0) {
        FUN_00781d3b((undefined4)(param_1[2]));
        param_1[2] = 0;
    }
    if (param_1[3] != 0) {
        FUN_00781d3b((undefined4)(param_1[3]));
        param_1[3] = 0;
    }
    if (param_1[4] != 0) {
        FUN_00781d3b((undefined4)(param_1[4]));
        param_1[4] = 0;
    }
    if (param_1[5] != 0) {
        FUN_00781d3b((undefined4)(param_1[5]));
        param_1[5] = 0;
    }
    if (param_1[6] != 0) {
        FUN_00781d3b((undefined4)(param_1[6]));
        param_1[6] = 0;
    }
    return;
}

}  // namespace seed_0059d500
