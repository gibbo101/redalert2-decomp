// 0x0059e8e0: function not yet identified
//
// Body: 114 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_0059e8e0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 )
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0059e8e0 {

struct Callee_0059e6d0 { void FUN_0059e6d0(char *param_2); };
extern undefined4  FUN_007820f4(int, int, int);
extern "C" undefined4 DAT_007e2af0;
extern "C" char DAT_00a70f0a;

struct Owner_0059e8e0 { void FUN_0059e8e0(undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5); };

void Owner_0059e8e0::FUN_0059e8e0(undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5)
{
    int param_1 = (int)this;
    undefined1 local_400 [1024];

    if (DAT_00a70f0a != '\0') {
        *(undefined4 *)(param_1 + 0x271c) = param_3;
        *(undefined4 *)(param_1 + 0x2720) = param_4;
        if (DAT_00a70f0a != '\0') {
            *(undefined4 *)(param_1 + 10000) = param_5;
        }
        FUN_007820f4((int)(local_400), (int)(&DAT_007e2af0), (int)(param_2));
        ((Callee_0059e6d0*)(param_1))->FUN_0059e6d0((char *)(local_400));
    }
    return;
}

}  // namespace seed_0059e8e0
