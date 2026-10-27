// 0x006056f0: function not yet identified
//
// Owner: DynamicVectorClass<HashObject<HashString, SchemeNode *>>, stores the DynamicVectorClass<HashObject<HashString, SchemeNode *>> vtable (constructor or destructor) (from RTTI/vtables).
// Body: 32 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_006056f0(undefined4 *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006056f0 {

extern "C" void* PTR_FUN_007a7b78;

void __fastcall FUN_006056f0(undefined4 *param_1)
{
    *(undefined1 *)(param_1 + 3) = 1;
    param_1[1] = 0;
    param_1[2] = 0;
    *(undefined1 *)((int)param_1 + 0xd) = 0;
    *param_1 = (undefined4)(&PTR_FUN_007a7b78);
    param_1[5] = 10;
    param_1[4] = 0;
    return;
}

}  // namespace seed_006056f0
