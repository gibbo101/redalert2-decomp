// 0x006e8440: function not yet identified
//
// Body: 147 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: undefined4 __thiscall FUN_006e8440(int param_1,uint param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order, return width) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_006e8440 {

extern "C" undefined4 DAT_00a35db4;
extern "C" undefined4 DAT_00a3d290;
extern "C" undefined4 DAT_00a3d298;

struct Owner_006e8440 { bool FUN_006e8440(uint param_2); };

bool Owner_006e8440::FUN_006e8440(uint param_2)
{
    int param_1 = (int)this;
    int iVar1;

    if ((param_2 != 0xfffffffd) && (param_2 != 0xfffffffe)) {
        if (param_2 >= *(uint *)(param_1 + 0x24)) {
            return 0;
        }
        iVar1 = (int)(*(int *)(*(int *)(param_1 + 0x18) + param_2 * 4));
        if (*(char *)(iVar1 + 0x28a) == '\0') {
            return 0;
        }
        if (*(char *)(iVar1 + 0x288) == '\0') {
            return 0;
        }
        if (((DAT_00a35db4 != 0) && (*(int *)(iVar1 + 0x28c) != -1)) &&
              (*(int *)(*(int *)(DAT_00a35db4 + 0x34) + 0xbc) != *(int *)(iVar1 + 0x28c))) {
            return 0;
        }
        if ((DAT_00a3d298 == 0) && (*(int *)(DAT_00a3d290 + 0x834) < *(int *)(iVar1 + 0x280))) {
            return 0;
        }
    }
    return 1;
}

}  // namespace seed_006e8440
