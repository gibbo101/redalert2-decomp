// 0x005293a0: function not yet identified
//
// Body: 43 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: bool __fastcall FUN_005293a0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005293a0 {

extern void __fastcall FUN_0052b560(void);

bool __fastcall FUN_005293a0(int param_1)
{
    if ((*(int *)(param_1 + 0xa4) == 0) && (*(char *)(param_1 + 0x2c4) != '\0')) {
        FUN_0052b560();
    }
    return *(int *)(param_1 + 0xa4) != 0;
}

}  // namespace seed_005293a0
