// 0x00797033: function not yet identified
//
// Body: 46 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 FUN_00797033(int param_1)
// Callees with accepted source:
//   FUN_00783605 -> src/recovered/00783605.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00797033 {

extern undefined4  FUN_00783605(short *param_1);
extern undefined4  FUN_00783689(short *param_1, short *param_2);
extern "C" undefined4 __cdecl _malloc(...);  // @ref __malloc=00782630

undefined4  FUN_00797033(int param_1)
{
    int iVar1;
    void *pvVar2;
    undefined4 uVar3;

    if (param_1 != 0) {
        iVar1 = (int)(FUN_00783605((short *)(param_1)));
        pvVar2 = (void *)(_malloc(iVar1 * 2 + 2));
        if (pvVar2 != (void *)0x0) {
            uVar3 = (undefined4)(FUN_00783689((short *)(pvVar2), (short *)(param_1)));
            return uVar3;
        }
    }
    return 0;
}

}  // namespace seed_00797033
