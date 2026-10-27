// 0x005abef0: function not yet identified
//
// Owner: MultiplayerSiegeAttackerTeam, virtual slot 0 (vtable +0x0) (from RTTI/vtables).
// Body: 36 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 * __thiscall FUN_005abef0(undefined4 *param_1,byte param_2)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005abef0 {

extern void __fastcall FUN_005b9b50(void);
extern void  FUN_00781d3b(undefined4 param_1);
extern "C" void* PTR_FUN_007a6c64;

struct Owner_005abef0 { undefined4 * FUN_005abef0(byte param_2); };

undefined4 * Owner_005abef0::FUN_005abef0(byte param_2)
{
    undefined4 * param_1 = (undefined4 *)this;
    *param_1 = (undefined4)(&PTR_FUN_007a6c64);
    FUN_005b9b50();
    if ((param_2 & 1) != 0) {
        FUN_00781d3b((undefined4)(param_1));
    }
    return param_1;
}

}  // namespace seed_005abef0
