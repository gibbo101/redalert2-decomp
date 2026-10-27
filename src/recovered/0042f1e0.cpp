// 0x0042f1e0: function not yet identified
//
// Body: 21 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: uint __fastcall FUN_0042f1e0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0042f1e0 {

uint __fastcall FUN_0042f1e0(int param_1)
{
    if (*(uint *)(param_1 + 0xc) != 0) {
        return *(uint *)(param_1 + 8) / *(uint *)(param_1 + 0xc);
    }
    return 0;
}

}  // namespace seed_0042f1e0
