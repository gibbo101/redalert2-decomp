// 0x007825e8: function not yet identified
//
// Body: 72 bytes (frozen inventory bound).
// Referenced from 156 sites (unconditional call).
// Ghidra prototype: void FUN_007825e8(LPVOID param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_007825e8 {

extern void  FUN_00785c86(int param_1);
extern void  FUN_00785ce7(int param_1);
extern undefined4  FUN_00787a4d(int param_1);
extern void  FUN_00787a78(uint *param_1, uint param_2);
extern "C" __declspec(dllimport) undefined4 __stdcall HeapFree(int, int, int);  // @ref __imp__HeapFree@12=0079a268
extern "C" undefined4 DAT_00b2b99c;

void  FUN_007825e8(LPVOID param_1)
{
    int iVar1;

    if (param_1 != (LPVOID)0x0) {
        FUN_00785c86((int)(9));
        iVar1 = (int)(FUN_00787a4d((int)(param_1)));
        if (iVar1 != 0) {
            FUN_00787a78((uint *)(iVar1), (uint)(param_1));
            FUN_00785ce7((int)(9));
            return;
        }
        FUN_00785ce7((int)(9));
        HeapFree((int)(DAT_00b2b99c), (int)(0), (int)(param_1));
    }
    return;
}

}  // namespace seed_007825e8
