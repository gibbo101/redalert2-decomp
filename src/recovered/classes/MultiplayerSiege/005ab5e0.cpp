// 0x005ab5e0: function not yet identified
//
// Owner: MultiplayerSiege, stores the MultiplayerSiege vtable (constructor or destructor) (from RTTI/vtables).
// Body: 11 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_005ab5e0(undefined4 *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005ab5e0 {

extern void __fastcall FUN_005b6e20(void);
extern "C" void* PTR_FUN_007a6b8c;

void __fastcall FUN_005ab5e0(undefined4 *param_1)
{
    *param_1 = (undefined4)(&PTR_FUN_007a6b8c);
    FUN_005b6e20();
    return;
}

}  // namespace seed_005ab5e0
