// 0x0072b0b0: function not yet identified
//
// Owner: VectorCursor<TRect<int>, VectorClass<TRect<int>>>, virtual slot 1 (vtable +0x4) (from RTTI/vtables).
// Body: 14 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: bool __fastcall FUN_0072b0b0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0072b0b0 {

bool __fastcall FUN_0072b0b0(int param_1)
{
    return *(uint *)(param_1 + 8) < *(uint *)(*(int *)(param_1 + 4) + 8);
}

}  // namespace seed_0072b0b0
