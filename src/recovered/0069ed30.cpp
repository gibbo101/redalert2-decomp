// 0x0069ed30: function not yet identified
//
// Body: 13 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_0069ed30(int *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0069ed30 {

extern "C" undefined4 DAT_00a40d2c;

void __fastcall FUN_0069ed30(int *param_1)
{
    if (*param_1 == -1) {
        *param_1 = DAT_00a40d2c;
    }
    return;
}

}  // namespace seed_0069ed30
