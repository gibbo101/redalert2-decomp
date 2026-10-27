// 0x004df760: function not yet identified
//
// Owner: GraphicMenuAnimItem, virtual slot 2 (vtable +0x8) (from RTTI/vtables).
// Body: 66 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 __thiscall FUN_004df760(int param_1,int *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_004df760 {

struct Owner_004df760 { undefined4 FUN_004df760(int *param_2); };

undefined4 Owner_004df760::FUN_004df760(int *param_2)
{
    int param_1 = (int)this;
    if (*(char *)(param_1 + 9) != '\0') {
        if ((*param_2 >= *(int *)(param_1 + 0x10)) &&
              (*param_2 < *(int *)(param_1 + 0x18) + *(int *)(param_1 + 0x10))) {
            if ((param_2[1] >= *(int *)(param_1 + 0x14)) &&
                  (param_2[1] < *(int *)(param_1 + 0x1c) + *(int *)(param_1 + 0x14))) {
                return 1;
            }
        }
    }
    return 0;
}

}  // namespace seed_004df760
