// 0x00467a00: function not yet identified
//
// Body: 32 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void FUN_00467a00(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order, return width) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_00467a00 {

extern void __cdecl FUN_00465f20(void);
extern void  FUN_00781d46(uint *param_1, uint *param_2, uint param_3, code *param_4);
extern "C" undefined4 DAT_008504a8;
extern "C" int DAT_008504e8;

void  FUN_00467a00(void)
{
    if (1 < DAT_008504e8) {
        FUN_00781d46((uint *)(&DAT_008504a8), (uint *)(DAT_008504e8), (uint)(4), (code *)(FUN_00465f20));
    }
    return;
}

}  // namespace seed_00467a00
