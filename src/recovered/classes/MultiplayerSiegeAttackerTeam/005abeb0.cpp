// 0x005abeb0: function not yet identified
//
// Owner: MultiplayerSiegeAttackerTeam, stores the MultiplayerSiegeAttackerTeam vtable (constructor or destructor) (from RTTI/vtables).
// Body: 11 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_005abeb0(undefined4 *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005abeb0 {

extern void __fastcall FUN_005b9b50(void);
extern "C" void* PTR_FUN_007a6c64;

void __fastcall FUN_005abeb0(undefined4 *param_1)
{
    *param_1 = (undefined4)(&PTR_FUN_007a6c64);
    FUN_005b9b50();
    return;
}

}  // namespace seed_005abeb0
