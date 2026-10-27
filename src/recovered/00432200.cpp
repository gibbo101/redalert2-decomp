// 0x00432200: function not yet identified
//
// Body: 98 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 * __thiscall FUN_00432200(undefined4 *param_1,byte param_2)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00432200 {

extern void  FUN_00781d3b(undefined4 param_1);
extern void  FUN_007825e8(LPVOID param_1);
extern "C" void* PTR_FUN_0079c788;

struct Owner_00432200 { undefined4 * FUN_00432200(byte param_2); };

undefined4 * Owner_00432200::FUN_00432200(byte param_2)
{
    undefined4 * param_1 = (undefined4 *)this;
    int iVar1;

    *param_1 = (undefined4)(&PTR_FUN_0079c788);
    if (param_1[2] != 0) {
        FUN_007825e8((LPVOID)(param_1[2]));
    }
    iVar1 = (int)(param_1[1]);
    if (iVar1 != 0) {
        if (*(int *)(iVar1 + 0x18) != 0) {
            FUN_00781d3b((undefined4)(*(int *)(iVar1 + 0x18)));
        }
        if (*(int *)(iVar1 + 0x1c) != 0) {
            FUN_00781d3b((undefined4)(*(int *)(iVar1 + 0x1c)));
        }
        FUN_00781d3b((undefined4)(iVar1));
    }
    if ((param_2 & 1) != 0) {
        FUN_00781d3b((undefined4)(param_1));
    }
    return param_1;
}

}  // namespace seed_00432200
