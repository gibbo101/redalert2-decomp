// 0x00620410: function not yet identified
//
// Body: 27 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: int __thiscall FUN_00620410(int param_1,uint param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00620410 {

struct Owner_00620410 { int FUN_00620410(uint param_2); };

int Owner_00620410::FUN_00620410(uint param_2)
{
    int param_1 = (int)this;
    if (param_2 < (uint)(int)*(short *)(param_1 + 6)) {
        return param_1 + 8 + param_2 * 0x18;
    }
    return 0;
}

}  // namespace seed_00620410
