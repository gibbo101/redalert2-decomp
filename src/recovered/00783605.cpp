// 0x00783605: function not yet identified
//
// Body: 29 bytes (frozen inventory bound).
// Referenced from 181 sites (unconditional call).
// Ghidra prototype: int FUN_00783605(short *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00783605 {

int  FUN_00783605(short *param_1)
{
    short sVar1;
    short *psVar2;

    sVar1 = (short)(*param_1);
    psVar2 = (short *)(param_1);
    while (psVar2 = psVar2 + 1, sVar1 != 0) {
        sVar1 = (short)(*psVar2);
    }
    return ((int)psVar2 - (int)param_1 >> 1) + -1;
}

}  // namespace seed_00783605
