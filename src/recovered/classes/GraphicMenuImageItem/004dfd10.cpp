// 0x004dfd10: function not yet identified
//
// Owner: GraphicMenuImageItem, virtual slot 2 (vtable +0x8) (from RTTI/vtables).
// Body: 66 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 __thiscall FUN_004dfd10(int param_1,int *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_004dfd10 {

struct Owner_004dfd10 { undefined4 FUN_004dfd10(int *param_2); };

undefined4 Owner_004dfd10::FUN_004dfd10(int *param_2)
{
    int param_1 = (int)this;
    if (*(char *)(param_1 + 9) != '\0') {
        if ((*param_2 >= *(int *)(param_1 + 0x14)) &&
              (*param_2 < *(int *)(param_1 + 0x1c) + *(int *)(param_1 + 0x14))) {
            if ((param_2[1] >= *(int *)(param_1 + 0x18)) &&
                  (param_2[1] < *(int *)(param_1 + 0x20) + *(int *)(param_1 + 0x18))) {
                return 1;
            }
        }
    }
    return 0;
}

}  // namespace seed_004dfd10
