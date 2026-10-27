// 0x00667780: function not yet identified
//
// Body: 108 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_00667780(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00667780 {

extern void  FUN_005b5ee0(void);
extern "C" __declspec(dllimport) undefined4 __stdcall Sleep(int);  // @ref __imp__Sleep@4=0079a1e4
extern "C" char DAT_00a40d28;

void __fastcall FUN_00667780(int param_1)
{
    int iVar1;

    if (DAT_00a40d28 != '\x01') {
        iVar1 = (int)(0);
        if (0 < *(int *)(param_1 + 0x2c)) {
            do {
                (**(code **)(**(int **)(*(int *)(param_1 + 0x20) + iVar1 * 4) + 4))();
                iVar1 = (int)(iVar1 + 1);
            } while (iVar1 < *(int *)(param_1 + 0x2c));
        }
        while (DAT_00a40d28 == '\0') {
            Sleep((int)(500));
            FUN_005b5ee0();
        }
        iVar1 = (int)(0);
        if (0 < *(int *)(param_1 + 0x2c)) {
            do {
                (**(code **)(**(int **)(*(int *)(param_1 + 0x20) + iVar1 * 4) + 8))();
                iVar1 = (int)(iVar1 + 1);
            } while (iVar1 < *(int *)(param_1 + 0x2c));
        }
    }
    return;
}

}  // namespace seed_00667780
