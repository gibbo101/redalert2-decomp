// 0x00522b20: function not yet identified
//
// Body: 85 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_00522b20(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_00522b20 {

extern "C" int DAT_00a521dc;
extern "C" undefined4 DAT_00a522b0;
extern "C" undefined4 DAT_00a522b4;
extern "C" undefined4 DAT_00a522b8;

void __fastcall FUN_00522b20(int param_1)
{
    int *piVar1;
    int iVar2;
    int *piVar3;

    if ((DAT_00a522b0 != 0) && (param_1 != 0)) {
        iVar2 = (int)(1);
        piVar3 = (int *)0x0;
        piVar1 = (int *)(DAT_00a522b4);
        if (1 < DAT_00a521dc) {
            do {
                if (*piVar1 == 0) {
                    if (piVar3 == (int *)0x0) {
                        piVar3 = (int *)(piVar1);
                    }
                }
                else if (*piVar1 == param_1) {
                    return;
                }
                iVar2 = (int)(iVar2 + 1);
                piVar1 = (int *)(piVar1 + 1);
            } while (iVar2 < DAT_00a521dc);
            if (piVar3 != (int *)0x0) {
                *piVar3 = param_1;
                DAT_00a522b8 = DAT_00a522b8 + 1;
            }
        }
    }
    return;
}

}  // namespace seed_00522b20
