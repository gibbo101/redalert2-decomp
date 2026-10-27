// 0x0071bd00: function not yet identified
//
// Body: 99 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: int __thiscall FUN_0071bd00(int param_1,int param_2,int param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0071bd00 {

extern "C" undefined4 __cdecl operator_new(...);  // @ref _operator_new=00782017

struct Owner_0071bd00 { int FUN_0071bd00(int param_2, int param_3); };

int Owner_0071bd00::FUN_0071bd00(int param_2, int param_3)
{
    int param_1 = (int)this;
    void *pvVar1;

    if (param_2 == 0) {
        pvVar1 = (void *)(operator_new(0x300));
        *(void **)(param_1 + 0x10) = pvVar1;
        *(undefined4 *)(param_1 + 0x18) = 1;
    }
    else {
        *(int *)(param_1 + 0x10) = param_2;
        *(undefined4 *)(param_1 + 0x18) = 0;
    }
    if (param_3 == 0) {
        pvVar1 = (void *)(operator_new(0x8000));
        *(void **)(param_1 + 0x14) = pvVar1;
        *(undefined4 *)(param_1 + 0x1c) = 1;
        return param_1;
    }
    *(int *)(param_1 + 0x14) = param_3;
    *(undefined4 *)(param_1 + 0x1c) = 0;
    return param_1;
}

}  // namespace seed_0071bd00
