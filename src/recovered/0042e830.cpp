// 0x0042e830: function not yet identified
//
// Body: 42 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __fastcall FUN_0042e830(int *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0042e830 {

void __fastcall FUN_0042e830(int *param_1)
{
    byte *pbVar1;
    int iVar2;
    int iVar3;

    if (param_1[0x18] != 0) {
        iVar3 = (int)(8);
        do {
            iVar2 = (int)(3);
            do {
                if (*param_1 != 0) {
                    pbVar1 = (byte *)(*param_1 + 0xc);
                    *pbVar1 = *pbVar1 & 0xfd;
                }
                param_1 = (int *)(param_1 + 1);
                iVar2 = (int)(iVar2 + -1);
            } while (iVar2 != 0);
            iVar3 = (int)(iVar3 + -1);
        } while (iVar3 != 0);
    }
    return;
}

}  // namespace seed_0042e830
