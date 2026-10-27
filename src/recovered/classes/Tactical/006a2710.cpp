// 0x006a2710: function not yet identified
//
// Owner: Tactical, stores the Tactical vtable (constructor or destructor) (from RTTI/vtables).
// Body: 42 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_006a2710(undefined4 *param_1)
// Callees with accepted source:
//   FUN_0040ff90 -> src/recovered/classes/AbstractClass/0040ff90.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006a2710 {

extern void __fastcall FUN_0040ff90(void);
extern "C" undefined4 DAT_0083996c;
extern "C" void* PTR_FUN_007ac544;
extern "C" void* PTR_FUN_007ac54c;
extern "C" void* PTR_FUN_007ac554;
extern "C" void* PTR_FUN_007ac570;

void __fastcall FUN_006a2710(undefined4 *param_1)
{
    *param_1 = (undefined4)(&PTR_FUN_007ac570);
    param_1[1] = (undefined4)(&PTR_FUN_007ac554);
    param_1[2] = (undefined4)(&PTR_FUN_007ac54c);
    param_1[3] = (undefined4)(&PTR_FUN_007ac544);
    DAT_0083996c = 0;
    FUN_0040ff90();
    return;
}

}  // namespace seed_006a2710
