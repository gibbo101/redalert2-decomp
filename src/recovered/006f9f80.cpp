// 0x006f9f80: function not yet identified
//
// Body: 44 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: bool FUN_006f9f80(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order, return width) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_006f9f80 {

extern undefined4  FUN_00781f20(byte *param_1, byte *param_2);
extern "C" undefined4 DAT_007f8da0;
extern "C" undefined4 DAT_007f8e34;

int  FUN_006f9f80(void)
{
    int iVar1;

    iVar1 = (int)(*(int *)(DAT_007f8da0 * 0x10 + 0x7f8cfc));
    if (iVar1 == 0) {
        return true;
    }
    iVar1 = (int)(FUN_00781f20((byte *)(iVar1), (byte *)(&DAT_007f8e34)));
    return iVar1 == 0;
}

}  // namespace seed_006f9f80
