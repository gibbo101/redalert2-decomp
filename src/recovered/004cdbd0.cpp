// 0x004cdbd0: function not yet identified
//
// Body: 15 bytes (frozen inventory bound).
// Referenced from 4 sites (data).
// Ghidra prototype: bool __fastcall FUN_004cdbd0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004cdbd0 {

bool __fastcall FUN_004cdbd0(int param_1)
{
    return *(int *)(param_1 + 0x4b4) == 0x1d;
}

}  // namespace seed_004cdbd0
