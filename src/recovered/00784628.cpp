// 0x00784628: function not yet identified
//
// Body: 35 bytes (frozen inventory bound).
// Referenced from 4 sites (unconditional call).
// Ghidra prototype: void FUN_00784628(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00784628 {

extern void  FUN_00785c86(int param_1);
extern "C" __declspec(dllimport) undefined4 __stdcall EnterCriticalSection(int);  // @ref __imp__EnterCriticalSection@4=0079a1dc

void  FUN_00784628(int param_1, int param_2)
{
    if (param_1 < 0x14) {
        FUN_00785c86((int)(param_1 + 0x1c));
        return;
    }
    EnterCriticalSection((int)((LPCRITICAL_SECTION)(param_2 + 0x20)));
    return;
}

}  // namespace seed_00784628
