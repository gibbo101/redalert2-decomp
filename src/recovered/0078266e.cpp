// 0x0078266e: function not yet identified
//
// Body: 78 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: LPVOID FUN_0078266e(uint param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078266e {

extern void  FUN_00785c86(int param_1);
extern void  FUN_00785ce7(int param_1);
extern undefined4  FUN_00787da3(uint *param_1);
extern "C" __declspec(dllimport) undefined4 __stdcall HeapAlloc(int, int, int);  // @ref __imp__HeapAlloc@12=0079a270
extern "C" undefined4 DAT_0082f214;
extern "C" undefined4 DAT_00b2b99c;

LPVOID  FUN_0078266e(uint param_1)
{
    LPVOID pvVar1;

    if (param_1 <= DAT_0082f214) {
        FUN_00785c86((int)(9));
        pvVar1 = (LPVOID)FUN_00787da3((uint *)(param_1));
        FUN_00785ce7((int)(9));
        if (pvVar1 != (LPVOID)0x0) {
            return pvVar1;
        }
    }
    if (param_1 == 0) {
        param_1 = (uint)(1);
    }
    pvVar1 = (LPVOID)(HeapAlloc((int)(DAT_00b2b99c), (int)(0), (int)(param_1 + 0xf & 0xfffffff0)));
    return pvVar1;
}

}  // namespace seed_0078266e
