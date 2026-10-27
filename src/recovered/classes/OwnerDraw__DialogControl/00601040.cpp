// 0x00601040: function not yet identified
//
// Owner: OwnerDraw::DialogControl, stores the OwnerDraw::DialogControl vtable (constructor or destructor) (from RTTI/vtables).
// Body: 7 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_00601040(undefined4 *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00601040 {

extern "C" void* PTR_FUN_007a7b28;

void __fastcall FUN_00601040(undefined4 *param_1)
{
    *param_1 = (undefined4)(&PTR_FUN_007a7b28);
    return;
}

}  // namespace seed_00601040
