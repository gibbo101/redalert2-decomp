// 0x00727c90: function not yet identified
//
// Body: 11 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __fastcall FUN_00727c90(undefined4 *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00727c90 {

extern void __fastcall FUN_00639510(void);
extern "C" void* PTR_FUN_007af0cc;

void __fastcall FUN_00727c90(undefined4 *param_1)
{
    *param_1 = (undefined4)(&PTR_FUN_007af0cc);
    FUN_00639510();
    return;
}

}  // namespace seed_00727c90
