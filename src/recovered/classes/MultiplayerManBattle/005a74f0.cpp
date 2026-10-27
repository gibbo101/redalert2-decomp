// 0x005a74f0: function not yet identified
//
// Owner: MultiplayerManBattle, stores the MultiplayerManBattle vtable (constructor or destructor) (from RTTI/vtables).
// Body: 11 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_005a74f0(undefined4 *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005a74f0 {

extern void __fastcall FUN_005b6e20(void);
extern "C" void* PTR_FUN_007a69dc;

void __fastcall FUN_005a74f0(undefined4 *param_1)
{
    *param_1 = (undefined4)(&PTR_FUN_007a69dc);
    FUN_005b6e20();
    return;
}

}  // namespace seed_005a74f0
