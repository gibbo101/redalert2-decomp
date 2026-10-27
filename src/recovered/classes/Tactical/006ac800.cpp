// 0x006ac800: function not yet identified
//
// Owner: Tactical, virtual slot 8 (vtable +0x20) (from RTTI/vtables).
// Body: 67 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 * __thiscall FUN_006ac800(undefined4 *param_1,byte param_2)
// Callees with accepted source:
//   FUN_0040ff90 -> src/recovered/classes/AbstractClass/0040ff90.cpp
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006ac800 {

extern void __fastcall FUN_0040ff90(void);
extern void  FUN_00781d3b(undefined4 param_1);
extern "C" undefined4 DAT_0083996c;
extern "C" void* PTR_FUN_007ac544;
extern "C" void* PTR_FUN_007ac54c;
extern "C" void* PTR_FUN_007ac554;
extern "C" void* PTR_FUN_007ac570;

struct Owner_006ac800 { undefined4 * FUN_006ac800(byte param_2); };

undefined4 * Owner_006ac800::FUN_006ac800(byte param_2)
{
    undefined4 * param_1 = (undefined4 *)this;
    *param_1 = (undefined4)(&PTR_FUN_007ac570);
    param_1[1] = (undefined4)(&PTR_FUN_007ac554);
    param_1[2] = (undefined4)(&PTR_FUN_007ac54c);
    param_1[3] = (undefined4)(&PTR_FUN_007ac544);
    DAT_0083996c = 0;
    FUN_0040ff90();
    if ((param_2 & 1) != 0) {
        FUN_00781d3b((undefined4)(param_1));
    }
    return param_1;
}

}  // namespace seed_006ac800
