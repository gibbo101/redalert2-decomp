// 0x00431f50: function not yet identified
//
// Body: 19 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __thiscall FUN_00431f50(int param_1,ushort *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00431f50 {

struct Owner_00431f50 { undefined4 FUN_00431f50(ushort *param_2); };

undefined4 Owner_00431f50::FUN_00431f50(ushort *param_2)
{
    int param_1 = (int)this;
    if (param_2 != (ushort *)0x0) {
        *param_2 = *param_2 ^ 0x5555;
    }
    return *(undefined4 *)(param_1 + 8);
}

}  // namespace seed_00431f50
