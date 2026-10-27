// 0x0042ebe0: function not yet identified
//
// Body: 56 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __thiscall FUN_0042ebe0(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0042ebe0 {

struct Callee_0042e990 { void FUN_0042e990(int param_2, int param_3); };

struct Owner_0042ebe0 { void FUN_0042ebe0(int param_2); };

void Owner_0042ebe0::FUN_0042ebe0(int param_2)
{
    int param_1 = (int)this;
    int iVar1;
    int *piVar2;

    if (*(int *)(param_1 + 0x60) != 0) {
        iVar1 = (int)(0);
        piVar2 = (int *)(param_1 + param_2 * 0xc);
        do {
            if (*piVar2 != 0) {
                ((Callee_0042e990*)(param_1))->FUN_0042e990((int)(param_2), (int)(iVar1));
            }
            iVar1 = (int)(iVar1 + 1);
            piVar2 = (int *)(piVar2 + 1);
        } while (iVar1 < 3);
    }
    return;
}

}  // namespace seed_0042ebe0
