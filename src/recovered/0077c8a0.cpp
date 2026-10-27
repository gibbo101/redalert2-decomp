// 0x0077c8a0: function not yet identified
//
// Body: 41 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_0077c8a0(int param_1,uint param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_0077c8a0 {

undefined4 __fastcall FUN_0077c8a0(int param_1, uint param_2)
{
    undefined4 uVar1;

    uVar1 = (undefined4)(0xffffffff);
    if ((0 < (int)param_2) && ((int)(uint)*(ushort *)(param_1 + 0xec) >= (int)param_2)) {
        uVar1 = (undefined4)(*(undefined4 *)(param_1 + 0x11c));
        *(uint *)(param_1 + 0x11c) = param_2 & 0xffff;
    }
    return uVar1;
}

}  // namespace seed_0077c8a0
