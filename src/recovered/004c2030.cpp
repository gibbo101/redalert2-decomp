// 0x004c2030: function not yet identified
//
// Body: 16 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_004c2030(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004c2030 {

undefined4 __fastcall FUN_004c2030(int param_1)
{
    if (0 < *(int *)(param_1 + 0x6c)) {
        return **(undefined4 **)(param_1 + 0x60);
    }
    return 0;
}

}  // namespace seed_004c2030
