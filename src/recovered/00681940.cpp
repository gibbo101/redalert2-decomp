// 0x00681940: function not yet identified
//
// Body: 53 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: uint __fastcall FUN_00681940(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00681940 {

uint __fastcall FUN_00681940(int param_1, int param_2, int unused_0)
{
    if (param_1 == 0x10) {
        return 2;
    }
    if ((param_1 != 0x28) && (param_1 != 3)) {
        if (param_1 == 7) {
            return (uint)(param_2 == 5);
        }
        return 0xffffffff;
    }
    return 3;
}

}  // namespace seed_00681940
