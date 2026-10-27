// 0x005a6230: function not yet identified
//
// Body: 73 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 __thiscall FUN_005a6230(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5, undefined4 param_6,undefined4 param_7,undefined4 *param_8)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order, return width) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_005a6230 {

extern void  FUN_00781d3b(undefined4 param_1);

struct Owner_005a6230 { bool FUN_005a6230(undefined4 param_2, int param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 *param_8); };

bool Owner_005a6230::FUN_005a6230(undefined4 param_2, int param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 *param_8)
{
    int param_1 = (int)this;
    *param_8 = 0;
    if (*(int *)(param_1 + 0x44) != 0) {
        if ((param_3 != 0) && ((*(uchar*)((char*)&param_5 + 1)) != '\0')) {
            FUN_00781d3b((undefined4)(param_3));
        }
        return 1;
    }
    if ((param_3 != 0) && ((*(uchar*)((char*)&param_5 + 1)) != '\0')) {
        FUN_00781d3b((undefined4)(param_3));
    }
    return 0;
}

}  // namespace seed_005a6230
