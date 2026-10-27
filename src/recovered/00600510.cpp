// 0x00600510: function not yet identified
//
// Body: 75 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: void __thiscall FUN_00600510(int param_1,short *param_2)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//   FUN_00783605 -> src/recovered/00783605.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00600510 {

extern void  FUN_00781d3b(undefined4 param_1);
extern undefined4  FUN_00783605(short *param_1);
extern void  FUN_00783689(short *param_1, short *param_2);
extern "C" undefined4 __cdecl operator_new(...);  // @ref _operator_new=00782017

struct Owner_00600510 { void FUN_00600510(short *param_2); };

void Owner_00600510::FUN_00600510(short *param_2)
{
    int param_1 = (int)this;
    int iVar1;
    void *pvVar2;

    if (*(int *)(param_1 + 0x28) != 0) {
        FUN_00781d3b((undefined4)(*(int *)(param_1 + 0x28)));
        *(undefined4 *)(param_1 + 0x28) = 0;
    }
    if ((param_2 != (short *)0x0) && (*param_2 != 0)) {
        iVar1 = (int)(FUN_00783605((short *)(param_2)));
        pvVar2 = (void *)(operator_new(iVar1 * 2 + 2));
        *(void **)(param_1 + 0x28) = pvVar2;
        FUN_00783689((short *)(pvVar2), (short *)(param_2));
    }
    return;
}

}  // namespace seed_00600510
