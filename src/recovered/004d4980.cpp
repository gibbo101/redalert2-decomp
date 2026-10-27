// 0x004d4980: function not yet identified
//
// Body: 32 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 * __thiscall FUN_004d4980(undefined4 *param_1,byte param_2)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004d4980 {

extern void  FUN_00781d3b(undefined4 param_1);
extern "C" void* PTR_FUN_007a2abc;

struct Owner_004d4980 { undefined4 * FUN_004d4980(byte param_2); };

undefined4 * Owner_004d4980::FUN_004d4980(byte param_2)
{
    undefined4 * param_1 = (undefined4 *)this;
    *param_1 = (undefined4)(&PTR_FUN_007a2abc);
    if ((param_2 & 1) != 0) {
        FUN_00781d3b((undefined4)(param_1));
    }
    return param_1;
}

}  // namespace seed_004d4980
