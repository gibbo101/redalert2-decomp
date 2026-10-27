// 0x0065b280: function not yet identified
//
// Body: 22 bytes (frozen inventory bound).
// Referenced from 5 sites (unconditional call).
// Ghidra prototype: int __fastcall FUN_0065b280(int *param_1)
// Callees with accepted source:
//   FUN_00795940 -> src/recovered/00795940.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0065b280 {

extern void __stdcall FUN_00795940(undefined4 param_1);

int __fastcall FUN_0065b280(int *param_1)
{
    if (*param_1 == 0) {
        FUN_00795940((undefined4)(0x80004003));
    }
    return *param_1;
}

}  // namespace seed_0065b280
