// 0x00667840: function not yet identified
//
// Owner: ScoreFontClass, stores the ScoreFontClass vtable (constructor or destructor) (from RTTI/vtables).
// Body: 43 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 * __fastcall FUN_00667840(undefined4 *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00667840 {

extern void  FUN_00667900(void);
extern "C" undefined4 DAT_00ab6fa4;
extern "C" void* PTR_FUN_007a92a0;

undefined4 * __fastcall FUN_00667840(undefined4 *param_1)
{
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[5] = 0;
    *param_1 = (undefined4)(&PTR_FUN_007a92a0);
    FUN_00667900();
    DAT_00ab6fa4 = DAT_00ab6fa4 + 1;
    return param_1;
}

}  // namespace seed_00667840
