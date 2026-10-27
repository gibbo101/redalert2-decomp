// 0x006fa0c0: function not yet identified
//
// Body: 47 bytes (frozen inventory bound).
// Referenced from 13 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_006fa0c0(ushort *param_1,byte *param_2,int param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006fa0c0 {

void __fastcall FUN_006fa0c0(ushort *param_1, byte *param_2, int param_3)
{
    byte bVar1;

    bVar1 = (byte)(*param_2);
    while ((bVar1 != 0 && (param_3 != 0))) {
        *param_1 = (ushort)bVar1;
        param_1 = (ushort *)(param_1 + 1);
        param_2 = (byte *)(param_2 + 1);
        if (param_3 != -1) {
            param_3 = (int)(param_3 + -1);
        }
        bVar1 = (byte)(*param_2);
    }
    *param_1 = 0;
    return;
}

}  // namespace seed_006fa0c0
