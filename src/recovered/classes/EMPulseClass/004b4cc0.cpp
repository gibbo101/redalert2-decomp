// 0x004b4cc0: function not yet identified
//
// Owner: EMPulseClass, stores the EMPulseClass vtable (constructor or destructor) (from RTTI/vtables).
// Body: 58 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 * __fastcall FUN_004b4cc0(undefined4 *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004b4cc0 {

extern void __fastcall FUN_0040ff10(void);
extern "C" undefined4 DAT_008559f0;
extern "C" void* PTR_FUN_007a0d8c;
extern "C" void* PTR_FUN_007a0d94;
extern "C" void* PTR_FUN_007a0d9c;
extern "C" void* PTR_FUN_007a0db8;

undefined4 * __fastcall FUN_004b4cc0(undefined4 *param_1)
{
    undefined4 uVar1;

    FUN_0040ff10();
    uVar1 = (undefined4)(DAT_008559f0);
    *param_1 = (undefined4)(&PTR_FUN_007a0db8);
    param_1[9] = uVar1;
    param_1[10] = 0;
    param_1[0xb] = 0;
    param_1[0xc] = 0;
    param_1[1] = (undefined4)(&PTR_FUN_007a0d9c);
    param_1[2] = (undefined4)(&PTR_FUN_007a0d94);
    param_1[3] = (undefined4)(&PTR_FUN_007a0d8c);
    return param_1;
}

}  // namespace seed_004b4cc0
