// 0x0069b120: function not yet identified
//
// Body: 76 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __thiscall FUN_0069b120(int param_1,int param_2)
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

namespace seed_0069b120 {

extern void  FUN_00781d3b(undefined4 param_1);
extern undefined4  FUN_00783605(short *param_1);
extern void  FUN_00783689(short *param_1, short *param_2);
extern "C" undefined4 __cdecl operator_new(...);  // @ref _operator_new=00782017

struct Owner_0069b120 { void FUN_0069b120(int param_2); };

void Owner_0069b120::FUN_0069b120(int param_2)
{
    int param_1 = (int)this;
    int iVar1;
    void *pvVar2;

    if (*(int *)(param_1 + 0x14) != 0) {
        FUN_00781d3b((undefined4)(*(int *)(param_1 + 0x14)));
        *(undefined4 *)(param_1 + 0x14) = 0;
    }
    if (param_2 != 0) {
        iVar1 = (int)(FUN_00783605((short *)(param_2)));
        pvVar2 = (void *)(operator_new(iVar1 * 2 + 2));
        *(void **)(param_1 + 0x14) = pvVar2;
        if (pvVar2 != (void *)0x0) {
            FUN_00783689((short *)(pvVar2), (short *)(param_2));
        }
    }
    return;
}

}  // namespace seed_0069b120
