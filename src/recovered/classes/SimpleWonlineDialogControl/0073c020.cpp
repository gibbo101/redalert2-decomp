// 0x0073c020: function not yet identified
//
// Owner: SimpleWonlineDialogControl, stores the SimpleWonlineDialogControl vtable (constructor or destructor) (from RTTI/vtables).
// Body: 11 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_0073c020(undefined4 *param_1)
// Callees with accepted source:
//   FUN_006010e0 -> src/recovered/classes/OwnerDraw__DialogControl/006010e0.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0073c020 {

extern void __fastcall FUN_006010e0(void);
extern "C" void* PTR_FUN_007af6f4;

void __fastcall FUN_0073c020(undefined4 *param_1)
{
    *param_1 = (undefined4)(&PTR_FUN_007af6f4);
    FUN_006010e0();
    return;
}

}  // namespace seed_0073c020
