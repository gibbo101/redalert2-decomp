// 0x0051ad10: function not yet identified
//
// Owner: CDFileClass, stores the CDFileClass vtable (constructor or destructor) (from RTTI/vtables).
// Body: 11 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_0051ad10(undefined4 *param_1)
// Callees with accepted source:
//   FUN_0042f350 -> src/recovered/classes/BufferIOFileClass/BufferIOFileClass_destructor_0042f350.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0051ad10 {

extern void __fastcall FUN_0042f350(void);
extern "C" void* PTR_FUN_0079a658;

void __fastcall FUN_0051ad10(undefined4 *param_1)
{
    *param_1 = (undefined4)(&PTR_FUN_0079a658);
    FUN_0042f350();
    return;
}

}  // namespace seed_0051ad10
