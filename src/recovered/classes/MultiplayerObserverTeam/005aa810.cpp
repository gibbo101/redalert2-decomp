// 0x005aa810: function not yet identified
//
// Owner: MultiplayerObserverTeam, virtual slot 0 (vtable +0x0) (from RTTI/vtables).
// Body: 30 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 __thiscall FUN_005aa810(undefined4 param_1,byte param_2)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005aa810 {

extern void __fastcall FUN_005b9b50(void);
extern void  FUN_00781d3b(undefined4 param_1);

struct Owner_005aa810 { undefined4 FUN_005aa810(byte param_2); };

undefined4 Owner_005aa810::FUN_005aa810(byte param_2)
{
    undefined4 param_1 = (undefined4)this;
    FUN_005b9b50();
    if ((param_2 & 1) != 0) {
        FUN_00781d3b((undefined4)(param_1));
    }
    return param_1;
}

}  // namespace seed_005aa810
