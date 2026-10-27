// 0x0078f162: function not yet identified
//
// Body: 78 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: void FUN_0078f162(int param_1)
// Callees with accepted source:
//   FUN_007825e8 -> src/recovered/007825e8.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_0078f162 {

extern void  FUN_007825e8(LPVOID param_1);
extern "C" undefined4 DAT_00b2b388;

void  FUN_0078f162(int param_1)
{
    if (((uint)(param_1) != (uint)(0)) && ((uint)(*(undefined **)(param_1 + 0xc)) != (uint)(&DAT_00b2b388))) {
        FUN_007825e8((LPVOID)(*(undefined **)(param_1 + 0xc)));
        FUN_007825e8((LPVOID)(*(undefined4 *)(param_1 + 0x10)));
        FUN_007825e8((LPVOID)(*(undefined4 *)(param_1 + 0x14)));
        FUN_007825e8((LPVOID)(*(undefined4 *)(param_1 + 0x18)));
        FUN_007825e8((LPVOID)(*(undefined4 *)(param_1 + 0x1c)));
        FUN_007825e8((LPVOID)(*(undefined4 *)(param_1 + 0x20)));
        FUN_007825e8((LPVOID)(*(undefined4 *)(param_1 + 0x24)));
    }
    return;
}

}  // namespace seed_0078f162
