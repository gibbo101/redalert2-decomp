// 0x00663490: function not yet identified
//
// Body: 79 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 FUN_00663490(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_00663490 {

extern "C" undefined4 DAT_00a35d0c;
extern "C" undefined4 DAT_00a35d64;
extern "C" undefined4 DAT_00a3d290;
extern "C" undefined4 DAT_00a3d298;
extern "C" undefined4 * DAT_00a3fa80;

undefined4  FUN_00663490(void)
{
    undefined4 uVar1;
    int iVar2;

    uVar1 = (undefined4)(0);
    if (DAT_00a3d298 == 0) {
        if (*(int *)(DAT_00a3d290 + 0x224c) != -1) {
            return *(undefined4 *)(*(int *)(DAT_00a35d64 + *(int *)(DAT_00a3d290 + 0x224c) * 4) + 0x98);
        }
    }
    else {
        iVar2 = (int)(*(int *)(*DAT_00a3fa80 + 0x4b));
        if (iVar2 == -3) {
            iVar2 = (int)(0);
        }
        uVar1 = (undefined4)(*(undefined4 *)(*(int *)(DAT_00a35d0c + iVar2 * 4) + 0xbc));
    }
    return uVar1;
}

}  // namespace seed_00663490
