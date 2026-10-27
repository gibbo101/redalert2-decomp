// 0x0044d030: function not yet identified
//
// Body: 63 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_0044d030(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0044d030 {

struct Owner_0044d030 { void FUN_0044d030(int param_2); };

void Owner_0044d030::FUN_0044d030(int param_2)
{
    int param_1 = (int)this;
    int *piVar1;
    int iVar2;

    if (param_2 == -2) {
        piVar1 = (int *)(param_1 + 0x454);
        iVar2 = (int)(0x12);
        do {
            if (*piVar1 != 0) {
                *(undefined1 *)(*piVar1 + 0x17d) = 1;
            }
            piVar1 = (int *)(piVar1 + 1);
            iVar2 = (int)(iVar2 + -1);
        } while (iVar2 != 0);
        return;
    }
    iVar2 = (int)(*(int *)(param_1 + 0x454 + param_2 * 4));
    if (iVar2 != 0) {
        *(undefined1 *)(iVar2 + 0x17d) = 1;
    }
    return;
}

}  // namespace seed_0044d030
