// 0x004bfb90: function not yet identified
//
// Body: 34 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: bool __thiscall FUN_004bfb90(int *param_1,int param_2)
// Callees with accepted source:
//   FUN_00795940 -> src/recovered/00795940.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004bfb90 {

extern void __stdcall FUN_00795940(undefined4 param_1);

struct Owner_004bfb90 { bool FUN_004bfb90(int param_2); };

bool Owner_004bfb90::FUN_004bfb90(int param_2)
{
    int * param_1 = (int *)this;
    if (param_2 != 0) {
        FUN_00795940((undefined4)(0x80004003));
    }
    return *param_1 == 0;
}

}  // namespace seed_004bfb90
