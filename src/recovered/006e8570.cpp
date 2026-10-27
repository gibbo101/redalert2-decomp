// 0x006e8570: function not yet identified
//
// Body: 30 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined * __thiscall FUN_006e8570(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_006e8570 {

extern "C" undefined4 DAT_007ce0ec;

struct Owner_006e8570 { undefined * FUN_006e8570(int param_2); };

undefined * Owner_006e8570::FUN_006e8570(int param_2)
{
    int param_1 = (int)this;
    if ((param_2 >= 0) && (param_2 < *(int *)(param_1 + 0x24))) {
        return *(undefined **)(*(int *)(param_1 + 0x18) + param_2 * 4);
    }
    return (unsigned char *)(&DAT_007ce0ec);
}

}  // namespace seed_006e8570
