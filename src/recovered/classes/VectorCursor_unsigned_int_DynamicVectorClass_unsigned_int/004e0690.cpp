// 0x004e0690: function not yet identified
//
// Owner: VectorCursor<unsigned int, DynamicVectorClass<unsigned int>>, virtual slot 1 (vtable +0x4) (from RTTI/vtables).
// Body: 14 bytes (frozen inventory bound).
// Referenced from 4 sites (computed call, data).
// Ghidra prototype: bool __fastcall FUN_004e0690(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004e0690 {

bool __fastcall FUN_004e0690(int param_1)
{
    return *(uint *)(param_1 + 8) < *(uint *)(*(int *)(param_1 + 4) + 0x10);
}

}  // namespace seed_004e0690
