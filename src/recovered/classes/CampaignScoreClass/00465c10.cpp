// 0x00465c10: function not yet identified
//
// Owner: CampaignScoreClass, stores the CampaignScoreClass vtable (constructor or destructor) (from RTTI/vtables).
// Body: 7 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_00465c10(undefined4 *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00465c10 {

extern "C" void* PTR_FUN_0079d724;

void __fastcall FUN_00465c10(undefined4 *param_1)
{
    *param_1 = (undefined4)(&PTR_FUN_0079d724);
    return;
}

}  // namespace seed_00465c10
