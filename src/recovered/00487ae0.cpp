// 0x00487ae0: function not yet identified
//
// Body: 109 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void __thiscall FUN_00487ae0(int param_1,ushort *param_2,char *param_3,int param_4,int param_5,ushort *param_6)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_00487ae0 {

extern "C" undefined4 DAT_00839c6c;

struct Owner_00487ae0 { void FUN_00487ae0(ushort *param_2, char *param_3, int param_4, int param_5, ushort *param_6, int unused_5, int unused_6, int unused_7); };

void Owner_00487ae0::FUN_00487ae0(ushort *param_2, char *param_3, int param_4, int param_5, ushort *param_6, int unused_5, int unused_6, int unused_7)
{
    int param_1 = (int)this;
    ushort *puVar1;
    int iVar2;

    puVar1 = (ushort *)(param_6);
    if (0 < param_4) {
        param_6 = (ushort *)param_4;
        iVar2 = (int)(DAT_00839c6c);
        do {
            if ((param_5 < (int)(uint)*puVar1) && (*param_3 != '\0')) {
                *param_2 = *param_2 >> 1 & *(ushort *)(param_1 + 4);
                *puVar1 = (ushort)param_5;
                iVar2 = (int)(DAT_00839c6c);
            }
            puVar1 = (ushort *)(puVar1 + 1);
            param_3 = (char *)(param_3 + 1);
            param_2 = (ushort *)(param_2 + 1);
            if (puVar1 >= *(ushort **)(iVar2 + 0x1c)) {
                puVar1 = (ushort *)((int)puVar1 - *(int *)(iVar2 + 0x20));
            }
            param_6 = (ushort *)((int)param_6 + -1);
        } while (param_6 != (ushort *)0x0);
    }
    return;
}

}  // namespace seed_00487ae0
