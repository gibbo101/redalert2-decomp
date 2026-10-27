// 0x005a22d0: function not yet identified
//
// Owner: DynamicVectorClass<char *>, virtual slot 0 (vtable +0x0) (from RTTI/vtables).
// Body: 73 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 * __thiscall FUN_005a22d0(undefined4 *param_1,byte param_2)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005a22d0 {

extern void  FUN_00781d3b(undefined4 param_1);
extern "C" void* PTR_FUN_007a6604;

struct Owner_005a22d0 { undefined4 * FUN_005a22d0(byte param_2); };

undefined4 * Owner_005a22d0::FUN_005a22d0(byte param_2)
{
    undefined4 * param_1 = (undefined4 *)this;
    *param_1 = (undefined4)(&PTR_FUN_007a6604);
    if ((param_1[1] != 0) && (*(char *)((int)param_1 + 0xd) != '\0')) {
        FUN_00781d3b((undefined4)(param_1[1]));
        param_1[1] = 0;
    }
    *(undefined1 *)((int)param_1 + 0xd) = 0;
    param_1[2] = 0;
    if ((param_2 & 1) != 0) {
        FUN_00781d3b((undefined4)(param_1));
    }
    return param_1;
}

}  // namespace seed_005a22d0
