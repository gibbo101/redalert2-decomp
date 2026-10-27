// 0x00728c30: function not yet identified
//
// Owner: WorldDominationTour::MapSizeGameOption, virtual slot 0 (vtable +0x0) (from RTTI/vtables).
// Body: 36 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 * __thiscall FUN_00728c30(undefined4 *param_1,byte param_2)
// Callees with accepted source:
//   FUN_00639710 -> src/recovered/classes/ReferenceCounted/00639710.cpp
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00728c30 {

extern void __fastcall FUN_00639710(void);
extern void  FUN_00781d3b(undefined4 param_1);
extern "C" void* PTR_FUN_007af118;

struct Owner_00728c30 { undefined4 * FUN_00728c30(byte param_2); };

undefined4 * Owner_00728c30::FUN_00728c30(byte param_2)
{
    undefined4 * param_1 = (undefined4 *)this;
    *param_1 = (undefined4)(&PTR_FUN_007af118);
    FUN_00639710();
    if ((param_2 & 1) != 0) {
        FUN_00781d3b((undefined4)(param_1));
    }
    return param_1;
}

}  // namespace seed_00728c30
