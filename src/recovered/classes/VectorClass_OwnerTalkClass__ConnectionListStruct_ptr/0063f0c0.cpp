// 0x0063f0c0: function not yet identified
//
// Owner: VectorClass<OwnerTalkClass::ConnectionListStruct *>, stores the VectorClass<OwnerTalkClass::ConnectionListStruct *> vtable (constructor or destructor) (from RTTI/vtables).
// Body: 106 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_0063f0c0(undefined4 *param_1)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0063f0c0 {

extern void  FUN_00781d3b(undefined4 param_1);
extern "C" void* PTR_FUN_007a900c;

void __fastcall FUN_0063f0c0(undefined4 *param_1)
{
    int iVar1;
    int iVar2;

    iVar1 = (int)(param_1[4]);
    while (iVar1 != 0) {
        FUN_00781d3b((undefined4)(*(undefined4 *)param_1[1]));
        if (0 < (int)param_1[4]) {
            iVar1 = (int)(param_1[4] + -1);
            iVar2 = (int)(0);
            param_1[4] = iVar1;
            if (0 < iVar1) {
                do {
                    iVar2 = (int)(iVar2 + 1);
                    *(undefined4 *)(param_1[1] + -4 + iVar2 * 4) = *(undefined4 *)(param_1[1] + iVar2 * 4);
                } while (iVar2 < (int)param_1[4]);
            }
        }
        iVar1 = (int)(param_1[4]);
    }
    *param_1 = (undefined4)(&PTR_FUN_007a900c);
    if ((param_1[1] != 0) && (*(char *)((int)param_1 + 0xd) != '\0')) {
        FUN_00781d3b((undefined4)(param_1[1]));
        param_1[1] = 0;
    }
    *(undefined1 *)((int)param_1 + 0xd) = 0;
    param_1[2] = 0;
    return;
}

}  // namespace seed_0063f0c0
