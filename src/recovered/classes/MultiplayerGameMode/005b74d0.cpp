// 0x005b74d0: function not yet identified
//
// Owner: MultiplayerGameMode, virtual slot 24 (vtable +0x60) (from RTTI/vtables).
// Body: 5 bytes (frozen inventory bound).
// Referenced from 7 sites (data).
// Ghidra prototype: void __fastcall FUN_005b74d0(int *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005b74d0 {

void __fastcall FUN_005b74d0(int *param_1)
{
                                        /* WARNING: Could not recover jumptable at 0x005b74d2. Too many branches */
                                        /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 0x5c))();
    return;
}

}  // namespace seed_005b74d0
