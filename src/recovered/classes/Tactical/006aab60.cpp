// 0x006aab60: function not yet identified
//
// Owner: Tactical, virtual slot 10 (vtable +0x28) (from RTTI/vtables).
// Body: 82 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_006aab60(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006aab60 {

struct Callee_00499070 { void FUN_00499070(undefined4 *param_2); };
extern "C" undefined4 DAT_008324e0;
extern "C" undefined4 DAT_0083366c;
extern "C" undefined4 DAT_00833670;
extern "C" undefined4 DAT_00833674;
extern "C" undefined4 DAT_00abe5f8;

void __stdcall FUN_006aab60(int param_1, int unused_1)
{
    int *piVar1;

    piVar1 = (int *)(&DAT_00abe5f8);
    do {
        if (*piVar1 == param_1) {
            *piVar1 = 0;
        }
        piVar1 = (int *)(piVar1 + 3);
    } while ((int)piVar1 < 0xabfd68);
    if (param_1 == DAT_0083366c) {
        ((Callee_00499070*)(&DAT_008324e0))->FUN_00499070((undefined4 *)(0));
        DAT_0083366c = 0;
        DAT_00833670 = 0;
        DAT_00833674 = 0xffffffff;
    }
    return;
}

}  // namespace seed_006aab60
