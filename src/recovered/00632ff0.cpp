// 0x00632ff0: function not yet identified
//
// Body: 15 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: bool __fastcall FUN_00632ff0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00632ff0 {

bool __fastcall FUN_00632ff0(int param_1)
{
    return *(int *)(param_1 + 0x14a8) == 1;
}

}  // namespace seed_00632ff0
