// 0x00730360: function not yet identified
//
// Body: 14 bytes (frozen inventory bound).
// Referenced from 15 sites (computed call, data).
// Ghidra prototype: bool __fastcall FUN_00730360(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00730360 {

bool __fastcall FUN_00730360(int param_1)
{
    return *(uint *)(param_1 + 8) < *(uint *)(*(int *)(param_1 + 4) + 0x10);
}

}  // namespace seed_00730360
