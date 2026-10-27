// 0x006203c0: function not yet identified
//
// Body: 11 bytes (frozen inventory bound).
// Referenced from 8 sites (unconditional call).
// Ghidra prototype: bool __fastcall FUN_006203c0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006203c0 {

bool __fastcall FUN_006203c0(int param_1)
{
    return *(int *)(param_1 + 100) != 0;
}

}  // namespace seed_006203c0
