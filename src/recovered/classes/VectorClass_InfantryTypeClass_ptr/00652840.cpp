// 0x00652840: function not yet identified
//
// Owner: VectorClass<InfantryTypeClass *>, stores the VectorClass<InfantryTypeClass *> vtable (constructor or destructor) (from RTTI/vtables).
// Body: 45 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_00652840(undefined4 *param_1)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00652840 {

extern void  FUN_00781d3b(undefined4 param_1);
extern "C" void* PTR_FUN_007a3118;

void __fastcall FUN_00652840(undefined4 *param_1)
{
    *param_1 = (undefined4)(&PTR_FUN_007a3118);
    if ((param_1[1] != 0) && (*(char *)((int)param_1 + 0xd) != '\0')) {
        FUN_00781d3b((undefined4)(param_1[1]));
        param_1[1] = 0;
    }
    *(undefined1 *)((int)param_1 + 0xd) = 0;
    param_1[2] = 0;
    return;
}

}  // namespace seed_00652840
