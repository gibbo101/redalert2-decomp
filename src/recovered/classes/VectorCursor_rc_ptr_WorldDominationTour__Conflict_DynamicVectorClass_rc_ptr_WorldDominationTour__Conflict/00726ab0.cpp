// 0x00726ab0: function not yet identified
//
// Owner: VectorCursor<rc_ptr<WorldDominationTour::Conflict>, DynamicVectorClass<rc_ptr<WorldDominationTour::Conflict>>>, virtual slot 1 (vtable +0x4) (from RTTI/vtables).
// Body: 14 bytes (frozen inventory bound).
// Referenced from 6 sites (computed call, data).
// Ghidra prototype: bool __fastcall FUN_00726ab0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00726ab0 {

bool __fastcall FUN_00726ab0(int param_1)
{
    return *(uint *)(param_1 + 8) < *(uint *)(*(int *)(param_1 + 4) + 0x10);
}

}  // namespace seed_00726ab0
